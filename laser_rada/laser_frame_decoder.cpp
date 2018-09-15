#include "laser_frame_decoder.h"

#include <QString>

laser_frame_decoder::laser_frame_decoder()
{

}
void laser_frame_decoder::decoder_data(QByteArray buf)
{
    int tmp=0;
   data_n=(buf[6]&0x00ff)*256+buf[7]&0x00ff;
   data_n =((data_n-5)/3);
   laser_spd=buf[8]&0x00ff;
   angle_offset=(buf[9]&0x00ff);
   angle_offset=angle_offset*256;
   tmp=buf[10]&0x00ff;
   angle_offset=angle_offset+tmp;
   start_angle=(buf[11]&0x00ff);

   start_angle=start_angle*256;
   tmp=buf[12]&0x00ff;
           start_angle=(start_angle) +tmp;

   for(int i=0;i<data_n;i++)
   {
     distance[i]=(buf[11+i*3]&0x00ff)*256+ (buf[11+i*3+1]&0x00ff);
       signal_data[i]=  (buf[11+i*3+2]&0x00ff);

   } //end of get dat inf


}
QString laser_frame_decoder::print_inf()
{
  QString inf;
  QString tmp;
  inf=inf.number(data_n);
  for(int i=0;i<data_n;i++)
   {
    // inf=inf+"\r\ndis=\t"+tmp.number(distance[i]);
    // inf=inf+"\tsignal=\t"+tmp.number(signal_data[i]);

   }//////////////end of for

return(inf);
}
