// Created by Dinies on 19/11/2018.

#include "Camera.hpp"
namespace MultiRobot {

  Camera::Camera( Environment & t_env,
      const Eigen::Vector2d &t_p,
      const Eigen::Vector2d &t_v,
      const double t_alpha,
      const double t_sigma,
      const double t_R,
      const double t_kappa,
      const Eigen::Matrix2d &t_K_v,
      const double t_K_alpha,
      const Eigen::Vector2d &t_lowLeftEdgeVoronoi,
      const Eigen::Vector2d &t_upRightEdgeVoronoi,
      const double t_delta_t,
      const cv::Scalar &t_color):
    m_env( t_env),
    m_p( t_p),
    m_v( t_v),
    m_alpha( t_alpha),
    m_sigma( t_sigma),
    m_R( t_R),
    m_kappa( t_kappa),
    m_K_v( t_K_v),
    m_K_alpha( t_K_alpha),
    m_lowLeftEdgeVoronoi( t_lowLeftEdgeVoronoi),
    m_upRightEdgeVoronoi( t_upRightEdgeVoronoi),
    m_delta_t(t_delta_t ),
    m_color( t_color)
  {
    computeMassAndCentroidalPersp();
    m_curr_t = 0;
    m_radius = 0.15;
  }



  bool Camera::isInsideVoronoi( 
      const double t_xCoord, const double t_yCoord ){

    return m_lowLeftEdgeVoronoi(0) <= t_xCoord &&
      t_xCoord <= m_upRightEdgeVoronoi(0) &&
      m_lowLeftEdgeVoronoi(1) <= t_yCoord &&
      t_yCoord <= m_upRightEdgeVoronoi(1);
  }


  double  Camera::computeSharedTerm(const discretePoint &t_point){

       Eigen::Vector2d x( t_point.coords.x, t_point.coords.y);

    double numExponent = pow( (x - m_p).norm() - m_R ,2);
    double denExponent = (2*pow(m_sigma,2));
    return exp( - numExponent/ denExponent ) * t_point.eventProbability;
  }

  Eigen::Vector2d Camera::computeCentroidalDirection( const discretePoint &t_point){

    Eigen::Vector2d x( t_point.coords.x, t_point.coords.y);
    Eigen::Vector2d num = x-m_p;
    double denom = (x - m_p).norm();
    double threshold = 0.000001;

    if ( num.norm() < threshold){
      return Eigen::Vector2d::Zero();
    } else{
      return num/denom;
    }
  }


  void Camera::computeMassAndCentroidalPersp(){
    
    std::vector< std::vector< discretePoint>>  eventValues = m_env.getEventValues();
    double mass = 0;
    Eigen::Vector2d incrementalCentroidalPersp(0,0);


    for ( int i = 0; i < eventValues.size(); ++i){
      std::vector< discretePoint> columnValues = eventValues.at(i);
      
      for ( int j = 0; j < columnValues.size(); ++j){
        discretePoint point = columnValues.at(j);

        if ( isInsideVoronoi( point.coords.x, point.coords.y)){

          double sharedTerm = computeSharedTerm( point);

          mass+= sharedTerm;

          Eigen::Vector2d centroidalDir = computeCentroidalDirection( point);

          incrementalCentroidalPersp += centroidalDir * sharedTerm;
        }
      }
    }
    m_massVoronoiCell = mass;
    m_centroidalPerspective = incrementalCentroidalPersp / mass;
  }

  double Camera::computeCentroidalAperture(){
    return 1 - ( m_centroidalPerspective.transpose() * m_v);
  }

  double Camera::computeCentroidalAngleOfView(
      const double t_centrAperture){
    double sqrtTerm =
      sqrt( pow(m_kappa - 1,2)* pow(t_centrAperture,2)
          + 4* m_kappa* t_centrAperture );
    double a = (m_kappa -1) *t_centrAperture ;
    double den = 2*m_kappa;
    double num =  a + sqrtTerm;
    double fration = num / den;
    double centroidalAngleOfView = acos( 1 - fration );
    return centroidalAngleOfView;
  }

  Eigen::Vector3d Camera::generateInput(){
    double gamma = computeCentroidalAperture();
    double centroidalAngleOfView = computeCentroidalAngleOfView( gamma);

    Eigen::Matrix2d eye= Eigen::Matrix2d::Identity();
    Eigen::Vector2d v_dot = m_K_v *( eye - ( m_v * m_v.transpose())) 
      * m_centroidalPerspective;
    
    double alpha_dot = - m_K_alpha * ( m_alpha - centroidalAngleOfView);


    Eigen::Vector3d  input( v_dot(0), v_dot(1), alpha_dot);
    return input;
  }

  void Camera::updateState(const Eigen::Vector3d &t_deltaState ){
    m_v(0)  = m_v(0) + (m_delta_t * t_deltaState(0));
    m_v(1)  = m_v(1) + (m_delta_t * t_deltaState(1));
    m_alpha  += m_delta_t * t_deltaState(2);

  }

  void Camera::evolve(){

    updateState( generateInput() );
    draw();
  };


  void Camera::evolveDummy(){

    Eigen::Vector2d v_dot( -0.1, +0.2);

    m_v = m_v + v_dot;
    draw();

  }

  std::vector< cv::Point2d> Camera::computePointsCameraDrawing(){

    std::vector< cv::Point2d> pointVec;
    pointVec.reserve(6);
    double theta = atan2( m_v(1), m_v(0));


    cv::Point2d pointCamCenter( m_p(0), m_p(1));
    const double angleLeftViewCone = theta + m_alpha;
   const double offMapRange = 15.0;

    Eigen::Vector2d leftOffRangePoint(offMapRange, 0.0);
    MyMath::rotate2D( leftOffRangePoint, angleLeftViewCone);
    cv::Point2d pLeftOff(m_p(0)+leftOffRangePoint(0),
        m_p(1)+leftOffRangePoint(1));
    pointVec.push_back(pLeftOff); 
    
    pointVec.push_back(pointCamCenter);

    Eigen::Vector2d leftNearPoint(m_radius, 0.0);
    MyMath::rotate2D( leftNearPoint, angleLeftViewCone);
    cv::Point2d pLeftNear(m_p(0)+leftNearPoint(0),
        m_p(1)+leftNearPoint(1));
    pointVec.push_back(pLeftNear);

    double curr_angle(theta + M_PI/2);
    double angle_offset( M_PI/3);
    for (int i = 0; i < 4; ++i) {
      Eigen::Vector2d currPoint(m_radius, 0.0);
      MyMath::rotate2D( currPoint, curr_angle );
      cv::Point2d p(m_p(0)+currPoint(0), m_p(1)+currPoint(1));
      pointVec.push_back(p);
      curr_angle += angle_offset;
    }

    const double angleRightViewCone = theta - m_alpha;
    Eigen::Vector2d rightNearPoint(m_radius, 0.0);
    MyMath::rotate2D( rightNearPoint, angleRightViewCone);
    cv::Point2d pRightNear(m_p(0)+rightNearPoint(0),
        m_p(1)+rightNearPoint(1));
    pointVec.push_back(pRightNear);

    pointVec.push_back(pointCamCenter);

    Eigen::Vector2d rightOffRangePoint(offMapRange, 0.0);
    MyMath::rotate2D( rightOffRangePoint, angleRightViewCone);
    cv::Point2d pRightOff(m_p(0)+rightOffRangePoint(0),
        m_p(1)+rightOffRangePoint(1));
    pointVec.push_back(pRightOff);  

    return pointVec;
  };


  void Camera::draw(){
    if ( m_drawingPoints.size() > 0){
      cv::Scalar milk= {227,246,253};
      m_env.drawCam( m_drawingPoints, m_p,milk);
    }
    m_drawingPoints = computePointsCameraDrawing();
    m_env.drawCam( m_drawingPoints, m_p,m_color);
  }

  void Camera::drawMassAndCentroidalPersp(){
    
    std::vector< std::vector< discretePoint>>  eventValues = m_env.getEventValues();
    double mass = 0;
    Eigen::Vector2d incrementalCentroidalPersp(0,0);

    cv::Scalar black = { 0, 0, 0};
    cv::Scalar milk= {227,246,253};
    cv::Scalar lightblue= {210,139,38};


    for ( int i = 0; i < eventValues.size(); ++i){
      std::vector< discretePoint> columnValues = eventValues.at(i);
      
      for ( int j = 0; j < columnValues.size(); ++j){
        discretePoint point = columnValues.at(j);

        
        if ( i == 100 && j ==100 ){
          std::cout<< "debug";
        }
        if ( isInsideVoronoi( point.coords.x, point.coords.y)){

          double sharedTerm = computeSharedTerm( point);
          mass+= sharedTerm;
          Eigen::Vector2d centroidalDir = computeCentroidalDirection( point);
          incrementalCentroidalPersp += centroidalDir * sharedTerm;
          m_env.drawMass( sharedTerm , point.coords, lightblue, black);

      //    std::cout << "commonTerm: "<< commonTerm<< ", incrCentroidalpersp: "<< incrementalCentroidalPersp << "\n";

        }
      }
    }
    m_massVoronoiCell = mass;
    m_centroidalPerspective = incrementalCentroidalPersp / mass;

    cv::Point2d start( m_p(0), m_p(1));
    Eigen::Vector2d cPerspDir = m_p + m_centroidalPerspective;
    cv::Point2d end( cPerspDir(0), cPerspDir(1));
    m_env.drawCentroidalPerspective( start, end, lightblue);
  }
  
  void Camera::drawVoronoi(){
    std::vector< std::vector< discretePoint>>  eventValues = m_env.getEventValues();

    cv::Scalar black = { 0, 0, 0};
    cv::Scalar milk= {227,246,253};
    cv::Scalar lightblue= {210,139,38};


    for ( int i = 0; i < eventValues.size(); ++i){
      std::vector< discretePoint> columnValues = eventValues.at(i);
      
      for ( int j = 0; j < columnValues.size(); ++j){
        discretePoint point = columnValues.at(j);

        if ( isInsideVoronoi( point.coords.x, point.coords.y)){

         m_env.drawDot(  point.coords, black);

        }
      }
    }
  }
}



