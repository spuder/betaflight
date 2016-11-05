//
// Menu element types
// XXX Upon separation, all OME would be renamed to CME_ or similar.
//

#pragma once

typedef long (*CMSEntryFuncPtr)(displayPort_t *, void *);

//type of elements

typedef enum
{
    OME_Label,
    OME_Back,
    OME_OSD_Exit,
    OME_Submenu,
    OME_Bool,
    OME_INT8,
    OME_UINT8,
    OME_UINT16,
    OME_INT16,
    OME_String,
    OME_FLOAT, //only up to 255 value and cant be 2.55 or 25.5, just for PID's
    //wlasciwosci elementow
#ifdef OSD
    OME_VISIBLE,
#endif
    OME_TAB,
    OME_END,

    // Debug aid
    OME_MENU,

    OME_MAX = OME_MENU
} OSD_MenuElement;

typedef struct
{
    char *text;
    OSD_MenuElement type;
    CMSEntryFuncPtr func;
    void *data;
    uint8_t flags;
} OSD_Entry;

// Bits in flags
#define PRINT_VALUE    0x01  // Value has been changed, need to redraw
#define PRINT_LABEL    0x02  // Text label should be printed
#define DYNAMIC        0x04  // Value should be updated dynamically

#define IS_PRINTVALUE(p) ((p)->flags & PRINT_VALUE)
#define SET_PRINTVALUE(p) { (p)->flags |= PRINT_VALUE; }
#define CLR_PRINTVALUE(p) { (p)->flags &= ~PRINT_VALUE; }

#define IS_PRINTLABEL(p) ((p)->flags & PRINT_LABEL)
#define SET_PRINTLABEL(p) { (p)->flags |= PRINT_LABEL; }
#define CLR_PRINTLABEL(p) { (p)->flags &= ~PRINT_LABEL; }

#define IS_DYNAMIC(p) ((p)->flags & DYNAMIC)


typedef long (*CMSMenuFuncPtr)(void);

/*
onExit function is called with self:
(1) Pointer to an OSD_Entry when cmsMenuBack() was called.
    Point to an OSD_Entry with type == OME_Back if BACK was selected.
(2) NULL if called from menu exit (forced exit at top level).
*/

typedef long (*CMSMenuOnExitPtr)(OSD_Entry *self);

typedef struct
{
    // These two are debug aids for menu content creators.
    char *GUARD_text;
    OSD_MenuElement GUARD_type;

    CMSMenuFuncPtr onEnter;
    CMSMenuOnExitPtr onExit;
    CMSMenuFuncPtr onGlobalExit;
    OSD_Entry *entries;
} CMS_Menu;

typedef struct
{
    uint8_t *val;
    uint8_t min;
    uint8_t max;
    uint8_t step;
} OSD_UINT8_t;

typedef struct
{
    int8_t *val;
    int8_t min;
    int8_t max;
    int8_t step;
} OSD_INT8_t;

typedef struct
{
    int16_t *val;
    int16_t min;
    int16_t max;
    int16_t step;
} OSD_INT16_t;

typedef struct
{
    uint16_t *val;
    uint16_t min;
    uint16_t max;
    uint16_t step;
} OSD_UINT16_t;

typedef struct
{
    uint8_t *val;
    uint8_t min;
    uint8_t max;
    uint8_t step;
    uint16_t multipler;
} OSD_FLOAT_t;

typedef struct
{
    uint8_t *val;
    uint8_t max;
    const char * const *names;
} OSD_TAB_t;

typedef struct
{
    char *val;
} OSD_String_t;
