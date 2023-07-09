#ifndef SESSION_H
#define SESSION_H


class Session
{
    int session_id;
public:
    Session();
    Session(int session_id);
    void setSession(int session_id);
    bool isInit();
};

#endif
