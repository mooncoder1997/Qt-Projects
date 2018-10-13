#ifndef LASER_FRAME_DECODER_H
#define LASER_FRAME_DECODER_H

#include <QString>

class laser_frame_decoder
{
public:
laser_frame_decoder();
    int laser_spd;
    int angle_offset;
    int start_angle;
    int  distance[500];
    int  signal_data[500];
    int data_n;
    int data_index;
   QString  print_inf();

void decoder_data(QByteArray buf);




};

#endif // LASER_FRAME_DECODER_H
