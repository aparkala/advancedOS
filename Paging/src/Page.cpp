#include "Page.h"

//constructor for memory
Page::Page() {
    pageId = -1;
    processId = -1;
    resetFields();
}

//constructor for processes
Page::Page(int pageIdIn, int processIdIn) {
    pageId = pageIdIn;
    processId = processIdIn;
    resetFields();
}

// constructor to copy
Page::Page(const Page &page) {
	this->pageId = page.pageId;
	this->processId = page.processId;
	this->inMemory = page.inMemory;
	this->lastReferencedTime = page.lastReferencedTime;
	this->loadTime = page.loadTime;
	this->referenceCounter = page.referenceCounter;
}
//TODO implement the code to maintain the attributes when the page is referenced including setting inMemory true
void Page::referencePage(long currentTime) {
    inMemory = true;
    lastReferencedTime = currentTime;
    referenceCounter+=1;
    if (loadTime == -1){
        loadTime = currentTime;
    }
}

void Page::resetFields() {
    inMemory = false;
    lastReferencedTime = -1;
    loadTime = -1;
    referenceCounter = 0;
}
