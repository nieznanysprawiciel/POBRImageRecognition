#ifndef CHANNELTOGREYSCALE_H
#define CHANNELTOGREYSCALE_H

#include "ImageProcessor.h"

enum class ColorChannel
{
	RedChannel = 2,
	GreeenChannel = 1,
	BlueChannel = 0
};


class ChannelToGreyScale : public ImageProcessor
{
private:
	int m_channelNum;
public:
	ChannelToGreyScale( const std::string& name, ColorChannel channel );

	virtual void Process( cv::Mat& srcImage, cv::Mat& destImage ) override;
};


class RedToGreyScale : public ChannelToGreyScale
{
private:
public:
	RedToGreyScale()
	: ChannelToGreyScale( "Kanał czerwony -> skala szarości", ColorChannel::RedChannel ) {}

};

class BlueToGreyScale : public ChannelToGreyScale
{
private:
public:
	BlueToGreyScale()
	: ChannelToGreyScale( "Kanał czerwony -> skala szarości", ColorChannel::BlueChannel ) {}

};

class GreenToGreyScale : public ChannelToGreyScale
{
private:
public:
	GreenToGreyScale()
	: ChannelToGreyScale( "Kanał czerwony -> skala szarości", ColorChannel::GreeenChannel ) {}

};


class HueToGreyScale : public ChannelToGreyScale
{
private:
public:
	HueToGreyScale()
	: ChannelToGreyScale( "Kanał barwy -> skala szarości", ColorChannel::RedChannel ) {}

};

class SaturationToGreyScale : public ChannelToGreyScale
{
private:
public:
	SaturationToGreyScale()
	: ChannelToGreyScale( "Kanał nasycienia -> skala szarości", ColorChannel::GreeenChannel ) {}

};

class LuminanceToGreyScale : public ChannelToGreyScale
{
private:
public:
	LuminanceToGreyScale()
	: ChannelToGreyScale( "Kanał jasności -> skala szarości", ColorChannel::BlueChannel ) {}

};

#endif // CHANNELTOGREYSCALE_H
