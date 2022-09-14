#define red     "\033[31m"
#define green   "\033[32m"
#define yellow  "\033[33m"
#define blue    "\033[34m"
#define magenta "\033[35m"
#define cyan    "\033[36m"
#define white   "\033[37m"
#define fiolet  "\033[38m"

#define bg_red     "\033[41m"
#define bg_green   "\033[42m"
#define bg_yellow  "\033[43m"
#define bg_blue    "\033[44m"
#define bg_magenta "\033[45m"
#define bg_cyan    "\033[46m"
#define bg_white   "\033[47m"
#define bg_fiolet  "\033[48m"

#define reset   "\033[0m"


#define CTRL(k) ((k) & 0x1f)

#define arrow_up    72
#define arrow_down  80
#define arrow_left  75
#define arrow_right 77

#define newl    '\n'
#define tab     '\t'
#define space   ' '

#define esc     27
#define del     127

#define moveUp      "\x1b[1A"
#define moveDown    "\x1b[1B"
#define moveRight   "\x1b[1C"
#define moveLeft    "\x1b[1D"

#define clearLine   "\33[2K"