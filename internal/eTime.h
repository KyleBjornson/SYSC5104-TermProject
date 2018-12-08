/*******************************************************************
*
*  DESCRIPTION: class Time for embedded mode
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian & Daniella Niyonkuru
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*        17/7/2015 (Last Modification)
*******************************************************************/

#ifndef __ETIME_H
#define __ETIME_H

/** include files **/
#include <string> // class string
#include <ostream>
#include <cstdlib>

/** System call includes **/
#include <hwTime.h>
/*
#include <unistd.h> //Unix spec
#include <time.h>   //Unix spec
*/

/** definitions **/
typedef int  Hours ;
typedef int  Minutes ;
typedef int  Seconds ;
typedef int  MSeconds ;
typedef int  MicSeconds ;

class Time
{
public:
  Time( Hours h = 0, Minutes m = 0, Seconds s = 0, MSeconds ms = 0, MicSeconds mics = 0)
    : hour( h )
    , min( m )
    , sec( s )
    , msec( ms )
    , micsec( mics)
    { normalize(); }
  
  Time( const std::string &t )
    { makeFrom(t); }
  /*
  Time( const clock_t mseconds )
    : hour( 0 )
    , min( 0 )
    , sec( 0 )
    , msec( 0 )
    , micsec( 0)
    { makeFrom( mseconds ); }
  */
  Time( const RTIME micseconds ) //wall-clock time
    : hour( 0 )
    , min( 0 )
    , sec( 0 )
    , msec( 0 )
    , micsec( 0)
    { makeFrom( micseconds ); }
  
  Time( const Time & ) ;       // copy constructor

  static Time currentTime();  // For Real-Time: returns the current system time 


  // ** Modifiers ** //
  Time &hours( const Hours & ) ;
  Time &minutes( const Minutes & ) ;
  Time &seconds( const Seconds & ) ;
  Time &mseconds( const MSeconds & ) ;
  Time &micseconds( const MicSeconds & ) ;

  // ** Queries ** // 
  const Hours    &hours() const ;
  const Minutes  &minutes() const ;
  const Seconds  &seconds() const ;
  const MSeconds &mseconds() const ;
  const MicSeconds &micseconds() const ;

  Time operator +( const Time & ) const ;  // addition operator
  Time operator -( const Time & ) const ;  // substraction operator

  Time &operator =( const Time & ) ;       // assignment operator
  bool operator ==( const Time & ) const ; // Equality test
  bool operator !=( const Time & ) const ; // HENRY compile fix

  Time &operator =( const std::string &t ) // assignment operator
    {makeFrom(t); return *this;}
  
  Time &operator -=( const Time &t ) ;
  Time &operator +=( const Time &t ) ;

  bool operator <( const Time & ) const ;  // comparison operator 

  bool operator >( const Time & ) const ;  // HENRY compile fix
  bool operator >=( const Time & ) const ; // HENRY compile fix
  bool operator <=( const Time & ) const ; // HENRY compile fix

  std::string asString() const ;

  long long asMsecs() const
    { return mseconds() + seconds() * 1000 + minutes() * 60000 + hours() * 3600 * 1000; }

  long long asMicsecs() const
    { return micseconds() + mseconds() * 1000 + seconds() * 1000 * 1000 + minutes() * 60000 * 1000 + hours() * 3600 * 1000 * 1000; }

  static const Time Zero ;
  static const Time Inf()  ;
  static void SetStartTime();
private:
  Hours hour  ;
  Minutes min ;
  Seconds sec ;
  MSeconds msec ;
  MicSeconds micsec ;
  
  Time &makeFrom( const std::string & ) ;
public:
  //Time &makeFrom( float miliseconds ) ;
  //Time &makeFrom( clock_t ) ;
  Time &makeFrom( RTIME ) ;
  Time &normalize() ;
  Time &adjust( int &, int &, int ) ;
};

/** inline methods **/
inline
const Hours &Time::hours() const
{
  return hour ;
}

inline
const Minutes &Time::minutes() const
{
  return min ;
}

inline
const Seconds &Time::seconds() const
{
  return sec ;
}

inline
const MSeconds &Time::mseconds() const
{
  return msec ;
}

inline
const MicSeconds &Time::micseconds() const
{
  return micsec ;
}

inline
Time &Time::hours( const Hours &h )
{
  hour = h ;
  return *this ;
}

inline
Time &Time::minutes( const Minutes &m )
{
  min = m ;
  normalize() ;
  return *this ;
}

inline
Time &Time::seconds( const Seconds &s )
{
  sec = s ;
  normalize() ;
  return *this ;
}

inline
Time &Time::mseconds( const MSeconds &ms )
{
  msec = ms ;
  normalize() ;
  return *this ;
}

inline
Time &Time::micseconds( const MicSeconds &mics )
{
  micsec = mics ;
  normalize() ;
  return *this ;
}

inline
Time &Time::operator -=( const Time &t )
{
  (*this) = (*this) - t ;
  return *this ;
}

inline
Time &Time::operator +=( const Time &t )
{
  (*this) = (*this) + t ;
  return *this ;
}

inline
std::ostream &operator <<( std::ostream &os, const Time &t )
{
  os << t.asString();
  return os;
}

#endif // __ETIME_H
