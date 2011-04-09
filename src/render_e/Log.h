/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef LOG_H
#define	LOG_H

#include <string>

namespace render_e {

/// Macro that logs a error message
#define FATAL(message) Log::LogMessage(__FILE__,__LINE__,message,Fatal)
/// Macro that logs a error message
#define ERROR(message) Log::LogMessage(__FILE__,__LINE__,message,Error)
/// Macro that logs a debug message
#define DEBUG(message) Log::LogMessage(__FILE__,__LINE__,message,Debug)
/// Macro that logs an info message
#define INFO(message) Log::LogMessage(__FILE__,__LINE__,message,Info)

enum LogType{
    /// Info messages
    Info,
    /// Debug messages
    Debug,
    /// Error - engine is in a undefined state
    Error,
    /// Crash of system
    Fatal
};

/// Simple logging class
/// todo implement publish-subscribe pattern
class Log {
public:
    Log();
    Log(const Log& orig);
    virtual ~Log();
    static void LogMessage(std::string file, int lineNo, std::string message, LogType logType = Debug);
private:

};
}
#endif	/* LOG_H */

