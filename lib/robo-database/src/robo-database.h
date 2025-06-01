#ifndef _ROBO_DATABASE_H
#define _ROBO_DATABASE_H

class Database{
    public:
        Database(const char* url); 
        bool get_data();
    private:
        const char* _url;

};

#endif // _ROBO_DATABASE_H