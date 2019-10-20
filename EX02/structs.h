#define MAXMEMORY 9500
#define MAXJOBS 15
#define PENDING 12312
#define DROPPED 13413
#define ACCEPTED 34231

typedef struct partition
{
     char name[5];
     int size;
     short busy;
     int pendingName;
     int pendingSize;
     int pendingTime;       
} PARTITION;

typedef struct job
{
     int name;
     int size;
     int pendingTime;
     int status;
     struct job *next;       
} JOB;

typedef struct report
{
     short finished;   
     char name[20];
     int timeTaken;
     int droppedJobs;
     float totalThroughput;       
} REPORT;

