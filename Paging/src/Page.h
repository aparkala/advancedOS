//
// Created by Ozcan Ergul on 31.07.2020.
//

#ifndef P4_PAGE_H
#define P4_PAGE_H


class Page {

private:

public:
    Page();
    Page(int pageIdIn, int processIdIn);
	Page(const Page &page);
    void referencePage(long currentTime);
    void resetFields();

    int pageId;
    int processId;

    //defined for shortcut purposes
    bool inMemory;

    long lastReferencedTime;
    long loadTime;
    int referenceCounter;

};


#endif //P4_PAGE_H
