struct RM_FileConfig {
    int recordSize;
    int freePage;
    int maxPageRecordNum;
    int curPageNum;

};

struct RM_PageConfig {
    int curRecordNum;
    int nextFreePage;
    char *bitmap;
}