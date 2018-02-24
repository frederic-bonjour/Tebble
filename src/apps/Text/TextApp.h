#ifndef _TextApp_H_
#define _TextApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"


class TextApp : public Runnable {

    private:

        String text;
        String fontName;
        int16_t x = 0;
        uint16_t textWidth = 0;

    protected:
        
        uint16_t getRunInterval() {
            return 80;
        }

        void wakeUp(GraphicContext* gc, Ambience* ambience);

    public:

        TextApp();
        void run(GraphicContext* gc, Ambience* ambience, unsigned long time);
        
        void setText(String t);
        void setText(String t, String f);

};

#endif