#ifndef _JOB_ACCESS_STATE_HPP
#define _JOB_ACCESS_STATE_HPP

struct _JOB_ACCESS_STATE
{
    struct _ACCESS_STATE *AccessState;
    void *PrimaryToken;
    void *CallerID;
};

#endif // _JOB_ACCESS_STATE_HPP