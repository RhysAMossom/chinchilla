#ifndef ros_arduinoNros_msgs_h
#define ros_arduinoNros_msgs_h

#include "WProgram.h"
#include "ros.h"

namespace arduinoNros
{

  class arduinoNros_msgs : public ros::Msg
  {
    public:
      unsigned int distance;
      unsigned char degree;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      union {
        unsigned int real;
        unsigned int base;
      } u_distance;
      u_distance.real = this->distance;
      *(outbuffer + offset + 0) = (u_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->distance);
      union {
        unsigned char real;
        unsigned char base;
      } u_degree;
      u_degree.real = this->degree;
      *(outbuffer + offset + 0) = (u_degree.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->degree);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        unsigned int real;
        unsigned int base;
      } u_distance;
      u_distance.base = 0;
      u_distance.base |= ((typeof(u_distance.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance.base |= ((typeof(u_distance.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      this->distance = u_distance.real;
      offset += sizeof(this->distance);
      union {
        unsigned char real;
        unsigned char base;
      } u_degree;
      u_degree.base = 0;
      u_degree.base |= ((typeof(u_degree.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      this->degree = u_degree.real;
      offset += sizeof(this->degree);
     return offset;
    }

    const char * getType(){ return "arduinoNros/arduinoNros_msgs"; };

  };

}
#endif
