#pragma once
class SIGKILL {
public:
    int Time, pID;

    // constructor
    SIGKILL(int Time_ = 0 , int pID_=0) {
        Time = Time_;
        pID = pID_;
    }
};