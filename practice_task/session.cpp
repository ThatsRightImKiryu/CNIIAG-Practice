#include "session.h"

Session::Session(){
    session_id = 0;
}

Session::Session(int session_id)
{
    this->session_id = session_id;
}

void Session::setSession(int session_id){
    this->session_id = session_id;
}

bool Session::isInit(){
    return session_id;
};
