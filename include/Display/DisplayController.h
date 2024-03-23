#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

// maybe ill want to use another display library, who knows
class GBDisplayController
{
    virtual void SetPixel();
    virtual void DrawLine();
}

#endif