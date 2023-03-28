#pragma once
class SIGKILL {
public:
    int Time, pID;

    // constructor
    SIGKILL(int Time_, int pID_) {
        Time = Time_;
        pID = pID_;
    }
};