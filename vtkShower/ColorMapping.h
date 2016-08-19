#ifndef COLORMAPPING_H_
#define COLORMAPPING_H_

#pragma once

class ColorMapping{
public:
	double max_val;
	double min_val;

public:
	ColorMapping(double maxval,double minval):max_val(maxval),min_val(minval){};

	unsigned int GetColor(double val)
	{
		unsigned char r,g,b,a;
		unsigned int tmp;
		double rate = (double)(val-min_val) / (double)(max_val-min_val);
		//APOOÌí¼Ó
		if (val <= min_val)
		{
			r = static_cast<unsigned char>(0x00);
			g = static_cast<unsigned char>(0x00);
			b = static_cast<unsigned char>(0xff);
		}
		else if (val >= max_val)
		{
			r = static_cast<unsigned char>(0xff);
			g = static_cast<unsigned char>(0x00);
			b = static_cast<unsigned char>(0x00);
		}
		//APOOÌí¼Ó½áÊø
		else if (rate < 0.25)
		{
			r = static_cast<unsigned char>(0x00);
			tmp=0xff*rate/0.25;
			g = static_cast<unsigned char>(tmp);
			b = static_cast<unsigned char>(0xff);
		}
		else if (rate < 0.5)
		{
			r = static_cast<unsigned char>(0x00);
			g = static_cast<unsigned char>(0xff);
			tmp = 0xff*(0.5-rate)/0.25;
			b = static_cast<unsigned char>(tmp);
		}
		else if (rate < 0.75)
		{
			tmp = 0xff*(rate-0.5)/0.25;
			r = static_cast<unsigned char>(tmp);
			g = static_cast<unsigned char>(0xff);
			b = static_cast<unsigned char>(0x00);
		}
		else
		{
			r = static_cast<unsigned char>(0xff);
			tmp = 0xff*(1-rate)/0.25;
			g = static_cast<unsigned char>(tmp);
			b = static_cast<unsigned char>(0x00);
		}
		a=static_cast<unsigned char>(0x00);
		tmp=a+(b<<8)+(g<<16)+(r<<24);
		return tmp;
	};
};

class Color
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

public:
	Color(unsigned int i)
	{
		a = static_cast<unsigned char>(i);
		b = static_cast<unsigned char>(i>>8);
		g = static_cast<unsigned char>(i>>16);
		r = static_cast<unsigned char>(i>>24);
	}
};



#endif