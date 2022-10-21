#include "calcdisignstyle.h"


QString calcDisignStyle::buttonWithSmallFont()
{
    return "QPushButton{"
            "border-style:solid;"
            "border-width:2px;"
            "border-radius:8px;"
            "font-size:14px;"
            "border-bottom-color: rgb(136, 138, 133);"
            "border-right-color: rgb(186, 189, 182);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(185, 185, 185, 255), stop:1 rgba(255, 255, 255, 255));"
            "}"
            "QPushButton::hover{"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(182, 182, 182, 255), stop:1 rgba(224, 224, 224, 255));"
            "}"
            "QPushButton::pressed{"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(177, 177, 177, 255), stop:1 rgba(255, 255, 255, 255));"
           "}";
}

QString calcDisignStyle::buttonWithBigFont()
{
    return "QPushButton{"
            "border-style:solid;"
            "border-width:2px;"
            "border-radius:8px;"
            "font-size:25px;"
            "border-bottom-color: rgb(136, 138, 133);"
            "border-right-color: rgb(186, 189, 182);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(185, 185, 185, 255), stop:1 rgba(255, 255, 255, 255));"
            "}"
            "QPushButton::hover{"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(182, 182, 182, 255), stop:1 rgba(224, 224, 224, 255));"
            "}"
            "QPushButton::pressed{"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(177, 177, 177, 255), stop:1 rgba(255, 255, 255, 255));"
           "}";
}

QString calcDisignStyle::buttonYellowStyle()
{
    return "QPushButton{"
            "border-style:solid;"
            "border-width:2px;"
            "border-radius:8px;"
            "border-bottom-color: rgb(136, 138, 133);"
            "border-right-color: rgb(186, 189, 182);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(233, 185, 110, 255), stop:1 rgba(243, 216, 146, 255));"
            "}"

            "QPushButton::hover{"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(233, 166, 61, 255), stop:1 rgba(243, 210, 123, 255));"
            "}"

            "QPushButton::pressed{"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(177, 177, 177, 255), stop:1 rgba(255, 255, 255, 255));"
           "}";
}

QString calcDisignStyle::buttonBlueStyle()
{
    return  "QPushButton{"
            "border-style:solid;"
            "border-width:2px;"
            "border-radius:8px;"
            "border-bottom-color: rgb(136, 138, 133);"
            "border-right-color: rgb(186, 189, 182);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(114, 223, 218, 255), stop:1 rgba(195, 246, 244, 255));"
            "}"

            "QPushButton::hover{"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(23, 223, 214, 255), stop:1 rgba(69, 246, 239, 255));"
            "}"

            "QPushButton::pressed{"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(114, 223, 218, 255), stop:1 rgba(195, 246, 244, 255));"
            "}";
}

