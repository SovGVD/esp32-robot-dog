
/* -------------------- */

typedef void (*menuItemFunction)();

const typedef struct menuItem_t {
 char title[16];
 char funcArg[16];
 menuItemFunction func;
 int menuId;
 int menuParentId;
} menuItem;

typedef struct menuGroup_t {
  int startIndex;
  int menuLength;
  
} menuGroup;
