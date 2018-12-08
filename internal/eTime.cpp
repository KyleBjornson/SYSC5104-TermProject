/*******************************************************************
*
*  DESCRIPTION: class Time
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*  Edited By: Mohammad Moallemi & Daniella Niyonkuru
* 
*  Date: 22/10/2008, 17/7015
* 
*  Email: moallemi@sce.carleton.ca, daniella.niyonkuru@carleton.ca
*  currentTime() bug fixed - Leveraged for Embedded CD-Boost
*******************************************************************/

/** include files **/
#include <eTime.h>      // base class
#include <stringp.h>     // operator + int
#include <hwTime.h>      // New time definition for bare-metal version

/** Hardware system call includes **/
//#include <hwsystem.h>

/** public data **/
const Time Time::Zero ;    // Zero constant
const Time Time::Inf() {return Time( 32767, 59, 59, 999, 999) ;}  // Infinity constant 
RTIME simStartTime;

/*******************************************************************
* Function Name: Time
* Description: copy constructor
********************************************************************/
Time::Time( const Time &t )
: hour( t.hours() )
, min( t.minutes() )
, sec( t.seconds() )
, msec( t.mseconds() )
, micsec( t.micseconds() )
{}

/*******************************************************************
* Function Name: operator +
********************************************************************/
Time Time::operator +( const Time &t ) const
{
  if ( *this == Time::Inf() || t == Time::Inf() )
    return Time::Inf();

  Time st( hours() + t.hours(),
     minutes() + t.minutes(),
     seconds() + t.seconds(),
     mseconds() + t.mseconds(), 
     micseconds() + t.micseconds() );

  //st.normalize();  // It's called by constructor and is not needed
  
  return st;
}

/*******************************************************************
* Function Name: opeartor -
********************************************************************/
Time Time::operator -( const Time &t ) const
{
  if ( *this == Time::Inf() || t == Time::Inf() )
    return Time::Inf();

  Time st( hours() - t.hours(),
     minutes() - t.minutes(),
     seconds() - t.seconds(),
     mseconds() - t.mseconds(),
     micseconds() - t.micseconds() );

  //st.normalize();  // It's called by constructor and is not needed
  return st; 
}

/*******************************************************************
* Function Name: operator ==
********************************************************************/
bool Time::operator ==( const Time &t ) const
{
  return ( hours()    == t.hours()    &&
     minutes()  == t.minutes()  &&
     seconds()  == t.seconds()  &&
     mseconds() == t.mseconds()   &&
     micseconds() == t.micseconds() );
}

//HENRY compile fix
bool Time::operator !=( const Time &t ) const
{
  return !((*this) == t);
}
/*******************************************************************
* Function Name: opeartor =
********************************************************************/
Time &Time::operator =( const Time &t )
{
  hour = t.hours();
  sec = t.seconds();
  min = t.minutes();
  msec = t.mseconds();
  micsec = t.micseconds();
  return *this;
}

/*******************************************************************
* Function Name: operator <<
********************************************************************/
bool Time::operator <( const Time &t ) const
{
  return( hours() < t.hours()    ||
        ( hours() == t.hours() &&
         ( minutes() < t.minutes()  ||
          ( minutes() == t.minutes()  &&
            ( seconds() < t.seconds() ||
             ( seconds() == t.seconds() &&
              ( mseconds() < t.mseconds() ||
               ( mseconds() == t.mseconds() &&
                 micseconds() < t.micseconds() ) ) ) ) ) ) ) ) ;
}

//HENRY compile fix
bool Time::operator >=( const Time &t ) const
{
  return !((*this) < t);
}

//HENRY compile fix
bool Time::operator <=( const Time &t ) const
{
  return (((*this) < t)||((*this) == t));
}

//HENRY compile fix
bool Time::operator >( const Time &t ) const
{
  return !((*this) <= t);
}

/*******************************************************************
* Function Name: asString
********************************************************************/
std::string Time::asString() const
{
  char buf[100];

  if (*this == Time::Inf())
    sprintf( buf, "..." );
  else
    sprintf( buf, "%02d:%02d:%02d:%03d:%03d", hours(), minutes(), seconds(), mseconds(), micseconds() );

  return std::string( buf );
}

/*******************************************************************
* Function Name: makeFrom
* Description: make from std::string
********************************************************************/
Time &Time::makeFrom( const std::string &str )
{
  sscanf( str.c_str(), "%d:%d:%d:%d", &hour, &min, &sec, &msec); micsec = 0;
  normalize();
  return *this;
}

/*******************************************************************
* Function Name: makeFrom
* Description: make from miliseconds
********************************************************************/
/*
Time &Time::makeFrom( const clock_t miliseconds )
{
  clock_t milsec = miliseconds;
  minutes( static_cast< int >( milsec/ (1000*60) ) ) ;
  milsec -= (minutes()*1000*60);
  seconds( static_cast< int >( milsec/1000 ) ) ;
  milsec -= (seconds()*1000);
  mseconds( static_cast< int >( milsec) );
  micseconds(0);//to be campatible with the old format
  normalize() ;
  return *this ;
}
*/
/*******************************************************************
* Function Name: makeFrom
* Description: make from xenomai RTIME 
********************************************************************/
Time &Time::makeFrom( const RTIME xentime )
{
  RTIME mictime = xentime; // need to divide by 1000 if using Xenomai
  minutes( static_cast< int >( mictime/ (1000*1000*60) ) ) ;
  mictime -= (minutes()*1000*1000*60);
  seconds( static_cast< int >( mictime/(1000*1000) ) ) ;
  mictime -= (seconds()*1000*1000);
  mseconds( static_cast< int >( mictime/1000) );
  mictime -= (mseconds()*1000);
  micseconds(static_cast< int >( mictime));
  normalize() ;
  return *this ;
}

/*******************************************************************
* Function Name: normalize
********************************************************************/
Time &Time::normalize()
{
  // 0..999 Microseconds
  adjust( micsec, msec , 1000 );

  // 0..999 Miliseconds
  adjust( msec, sec , 1000 );

  // 0..59 seconds
  adjust( sec , min , 60   );

  // 0..59 minutes
  adjust( min , hour, 60   );

  return *this ;
}

/*******************************************************************
* Function Name: adjust
********************************************************************/
Time &Time::adjust( int &left, int &right, int maxVal )
{
  if( left >= maxVal )
  {
    right += left / maxVal ;
    left %= maxVal ;
  } else if( left < 0 )
  {
    register int aux = std::abs( left / maxVal ) + ( left % maxVal == 0 ? 0 : 1 );
    right -= aux ;
    left += maxVal * aux ;
  }
  return *this ;
}

/*******************************************************************
* Function Name: currentTime
********************************************************************/
/* static */
Time Time::currentTime()
{
  // Wall-clock real time
  Time st( rt_timer_read() - simStartTime );       // create from microseconds a Time

  return st;



}//currentTime
/*******************************************************************
* Function Name: set start time using xenomai 
********************************************************************/
void Time::SetStartTime()
{
	simStartTime = rt_timer_read();
}
