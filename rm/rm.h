class RM_RecordManager {
    public:
        RM_RecordManager() {}
        ~RM_RecordManager() {}

        void createFile(int recordSize) {}
        void destroyFile() {}
        void openFile() {}
        void closeFile() {}
};

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