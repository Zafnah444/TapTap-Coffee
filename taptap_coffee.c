#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define MAX_INGREDIENTS  80
#define NORMAL_MENU_COUNT 12
#define MAX_NORMAL_CART_LINES 30
#define BASE_COUNT 64
#define TOPPING_COUNT 100
#define BASE_CATS 6
#define TOPPING_CATS 4
#define PAGE_SIZE 10

struct Ingredient {
    char name[60];
    int price;
    int ml;
    int category;
};

struct NormalItem {
    char name[60];
    char desc[120];
    int price;
};

struct CupSize {
    char name[30];
    int ml;
    int index;
};

struct NormalCartEntry {
    int id;
    int qty;
    int ice;
    int caffeine;
    int whip;
    int boba;
};

struct CartEntry {
    int index;
    int isTopping;
    int portions;
};

struct Ingredient baseIngredients[BASE_COUNT] = {
    {"Whole Milk", 30, 200, 0},
    {"Skim Milk", 70, 200, 0},
    {"Heavy Cream", 90, 200, 0},
    {"Condensed Milk", 30, 20, 0},
    {"Evaporated Milk", 90, 200, 0},
    {"Buttermilk", 100, 200, 0},
    {"Goat Milk", 80, 200, 0},
    {"Buffalo Milk", 80, 200, 0},

    {"Almond Milk", 150, 200, 1},
    {"Oat Milk", 150, 200, 1},
    {"Soy Milk", 150, 200, 1},
    {"Coconut Milk", 150, 200, 1},
    {"Rice Milk", 150, 200, 1},
    {"Pistachio Milk", 150, 200, 1},
    {"Cashew Milk", 150, 200, 1},
    {"Macadamia Milk", 150, 200, 1},
    {"Hazelnut Milk", 150, 200, 1},
    {"Hemp Milk", 150, 200, 1},
    {"Tiger Nut Milk", 150, 200, 1},

    {"Chilled Water", 10, 200, 2},
    {"Sparkling Water (Seltzer)", 15, 200, 2},
    {"Club Soda", 15, 200, 2},
    {"Tonic Water", 18, 200, 2},
    {"Ginger Ale", 20, 200, 2},
    {"Lemon-Lime Soda", 20, 200, 2},
    {"Coconut Water", 25, 200, 2},
    {"Maple Water", 35, 200, 2},
    {"Cactus Water", 40, 200, 2},
    {"Aloe Vera Juice", 30, 200, 2},

    {"Green Tea", 12, 5, 3},
    {"Black Tea", 12, 5, 3},
    {"Oolong Tea", 15, 5, 3},
    {"Matcha", 25, 5, 3},
    {"White Tea", 20, 5, 3},
    {"Yellow Tea", 22, 5, 3},
    {"Earl Grey", 15, 5, 3},
    {"Masala Chai", 18, 5, 3},
    {"Milk Tea", 18, 5, 3},
    {"Rooibos", 15, 5, 3},
    {"Hibiscus Tea", 15, 5, 3},
    {"Chamomile Tea", 15, 5, 3},
    {"Peppermint Tea", 15, 5, 3},
    {"Lemon Balm Tea", 15, 5, 3},
    {"Butterfly Pea Flower Tea", 20, 5, 3},

    {"Double Shot Espresso", 200, 60, 4},
    {"Single Espresso", 200, 60, 4},
    {"Americano", 180, 150, 4},
    {"Cold Brew", 180, 100, 4},

    {"Sugarcane Juice", 25, 200, 5},
    {"Lemonade", 23, 200, 5},
    {"Fresh Lime Juice", 23, 200, 5},
    {"Orange Juice", 80, 200, 5},
    {"Red Apple Juice", 80, 200, 5},
    {"Green Apple Juice", 80, 200, 5},
    {"Pomegranate Juice", 80, 200, 5},
    {"White Grape Juice", 80, 200, 5},
    {"Red Grape Juice", 80, 200, 5},
    {"Cranberry Juice", 80, 200, 5},
    {"Pineapple Juice", 80, 200, 5},
    {"Mango Juice", 80, 200, 5},
    {"Papaya Juice", 80, 200, 5},
    {"Guava Juice", 80, 200, 5},
    {"Passionfruit Juice", 80, 200, 5},
    {"Watermelon Juice", 80, 200, 5}
};

struct Ingredient toppingIngredients[TOPPING_COUNT] = {
    {"Mango", 38, 100, 0},
    {"Banana", 35, 100, 0},
    {"Pineapple", 38, 100, 0},
    {"Canned Blueberry", 40, 100, 0},
    {"Wild Blueberry", 55, 100, 0},
    {"Papaya", 35, 100, 0},
    {"Blackberry", 50, 100, 0},
    {"Strawberry", 40, 100, 0},
    {"Wild Strawberry", 52, 100, 0},
    {"Raspberry", 48, 100, 0},
    {"Black Raspberry", 52, 100, 0},
    {"Golden Raspberry", 55, 100, 0},
    {"Kiwi", 42, 100, 0},
    {"Golden Kiwi", 50, 100, 0},
    {"Peach", 42, 100, 0},
    {"White Peach", 48, 100, 0},
    {"Passionfruit", 50, 100, 0},
    {"Dragonfruit (Red and White)", 52, 100, 0},
    {"Watermelon", 35, 100, 0},
    {"Guava", 38, 100, 0},
    {"Pink Guava", 42, 100, 0},
    {"Lychee", 45, 100, 0},
    {"Green Apple", 38, 100, 0},
    {"Red Apple", 38, 100, 0},
    {"Cranberry", 45, 100, 0},
    {"Gooseberry", 48, 100, 0},
    {"Date", 40, 100, 0},
    {"Jackfruit", 42, 100, 0},
    {"Tamarind", 40, 100, 0},
    {"Blood Orange", 48, 100, 0},
    {"Tangerine", 42, 100, 0},
    {"Grapefruit", 42, 100, 0},

    {"Crushed Dark Chocolate (70%+)", 25, 50, 1},
    {"Milk Chocolate Chips", 20, 50, 1},
    {"White Chocolate Sauce", 22, 50, 1},
    {"Raw Cocoa Powder", 18, 50, 1},
    {"Dutch-Processed Cocoa Powder", 20, 50, 1},
    {"Caramel Sauce", 18, 50, 1},
    {"Salted Caramel", 20, 50, 1},
    {"Butterscotch", 18, 50, 1},
    {"Toffee", 18, 50, 1},
    {"Peanut Butter", 20, 50, 1},
    {"Creamy Almond Butter", 28, 50, 1},
    {"Cashew Butter", 30, 50, 1},
    {"Hazelnut Butter", 32, 50, 1},
    {"Nutella", 25, 50, 1},
    {"Cookie Butter (Biscoff)", 28, 50, 1},
    {"Crushed Oreos", 20, 50, 1},
    {"Graham Cracker Crumbs", 15, 50, 1},
    {"Malted Milk Powder", 18, 50, 1},
    {"Marshmallow Fluff", 18, 50, 1},
    {"Condensed Milk Drizzle", 15, 50, 1},
    {"Maple Syrup", 22, 50, 1},
    {"Dark Molasses", 18, 50, 1},
    {"Jaggery Syrup", 15, 50, 1},
    {"Instant Coffee", 15, 50, 1},

    {"Fresh Mint Leaves", 8, 5, 2},
    {"Peppermint", 8, 5, 2},
    {"Basil Seeds", 10, 5, 2},
    {"Chia Seeds", 10, 5, 2},
    {"Fresh Lemongrass", 10, 5, 2},
    {"Crushed Fresh Ginger", 10, 5, 2},
    {"Whole Green Cardamom", 12, 5, 2},
    {"Black Cardamom", 15, 5, 2},
    {"Cinnamon Sticks", 10, 5, 2},
    {"Ground Cinnamon", 8, 5, 2},
    {"Whole Cloves", 10, 5, 2},
    {"Star Anise", 12, 5, 2},
    {"Vanilla Bean Paste", 20, 5, 2},
    {"Pure Vanilla Extract", 18, 5, 2},
    {"Lavender Buds", 15, 5, 2},
    {"Rose Water", 15, 5, 2},
    {"Orange Blossom Water", 15, 5, 2},
    {"Fresh Rosemary", 10, 5, 2},
    {"Thyme Sprigs", 10, 5, 2},
    {"Sage Leaves", 10, 5, 2},
    {"Lemon Verbena", 12, 5, 2},
    {"Crushed Pepper", 8, 5, 2},
    {"Chili Flakes", 8, 5, 2},
    {"Cayenne Pepper", 8, 5, 2},
    {"Ground Turmeric", 8, 5, 2},
    {"Fresh Sliced Turmeric Root", 10, 5, 2},
    {"Allspice", 10, 5, 2},
    {"Fennel Seeds", 8, 5, 2},
    {"Coriander Seeds", 8, 5, 2},

    {"Tapioca Boba Pearls (Black and Brown Sugar)", 50, 30, 3},
    {"Crystal Boba", 52, 30, 3},
    {"Popping Boba (Mango, Strawberry, Lychee)", 55, 30, 3},
    {"Coconut Jelly (Nata de Coco)", 48, 30, 3},
    {"Coffee Jelly", 50, 30, 3},
    {"Aloe Vera Chunks", 50, 30, 3},
    {"Grass Jelly", 48, 30, 3},
    {"Red Bean Paste (Anko)", 52, 30, 3},
    {"Mochi Pieces", 55, 30, 3},
    {"Basil Seeds (Subja)", 42, 30, 3},
    {"Chia Seeds (Gelatinous)", 42, 30, 3},
    {"Aloe Vera Pulp", 48, 30, 3},
    {"Seaweed Caviar (Agar Pearls)", 58, 30, 3},
    {"Taro Chunks", 52, 30, 3},
    {"Sweet Corn Kernels", 45, 30, 3}
};

int baseCatCount[BASE_CATS] = {8, 11, 10, 15, 4, 16};
int baseCatStart[BASE_CATS] = {0, 8, 19, 29, 44, 48};
const char *baseCatNames[BASE_CATS] = {
    "Dairy Milks & Creams",
    "Plant-Based & Nut Milks",
    "Refreshing Waters & Hydrators",
    "Teas & Botanical Infusions",
    "Coffees & Caffeinated Brews",
    "Acids, Juices, & Ferments"
};

int toppingCatCount[TOPPING_CATS] = {32, 24, 29, 15};
int toppingCatStart[TOPPING_CATS] = {0, 32, 56, 85};
const char *toppingCatNames[TOPPING_CATS] = {
    "Fruits",
    "Confectionery & Rich Profiles",
    "Herbal, Botanical, Floral, & Spice Add-ins",
    "Chewable, Viscous, & Textural Add-ins"
};

struct CupSize cupSizes[4];
struct NormalItem normalMenu[NORMAL_MENU_COUNT];
struct CartEntry cart[MAX_INGREDIENTS];
int cartSize = 0;
Font customFont;

void initData(void) {
    strcpy(cupSizes[0].name, "Solo cup");
    cupSizes[0].ml = 60;
    cupSizes[0].index = 0;

    strcpy(cupSizes[1].name, "Pixie");
    cupSizes[1].ml = 260;
    cupSizes[1].index = 1;

    strcpy(cupSizes[2].name, "Midi");
    cupSizes[2].ml = 500;
    cupSizes[2].index = 2;

    strcpy(cupSizes[3].name, "Colossal");
    cupSizes[3].ml = 700;
    cupSizes[3].index = 3;

    strcpy(normalMenu[0].name, "Classic Lemonade");
    strcpy(normalMenu[0].desc, "Freshly squeezed lemon, sugar and ice");
    normalMenu[0].price = 80;

    strcpy(normalMenu[1].name, "Mango Smoothie");
    strcpy(normalMenu[1].desc, "Blended mango with milk and ice");
    normalMenu[1].price = 120;

    strcpy(normalMenu[2].name, "Iced Americano");
    strcpy(normalMenu[2].desc, "Double shot espresso over ice");
    normalMenu[2].price = 150;

    strcpy(normalMenu[3].name, "Strawberry Milkshake");
    strcpy(normalMenu[3].desc, "Strawberry blended with milk and cream");
    normalMenu[3].price = 130;

    strcpy(normalMenu[4].name, "Coconut Cooler");
    strcpy(normalMenu[4].desc, "Chilled coconut water with basil seeds");
    normalMenu[4].price = 90;

    strcpy(normalMenu[5].name, "Chocolate Delight");
    strcpy(normalMenu[5].desc, "Rich chocolate milk with crushed ice");
    normalMenu[5].price = 140;

    strcpy(normalMenu[6].name, "Pineapple Fizz");
    strcpy(normalMenu[6].desc, "Blended pineapple with soda and mint");
    normalMenu[6].price = 100;

    strcpy(normalMenu[7].name, "Banana Boost");
    strcpy(normalMenu[7].desc, "Blended banana with milk and honey");
    normalMenu[7].price = 110;

    strcpy(normalMenu[8].name, "Blueberry Blast");
    strcpy(normalMenu[8].desc, "Blueberry blended with yogurt");
    normalMenu[8].price = 160;

    strcpy(normalMenu[9].name, "Papaya Paradise");
    strcpy(normalMenu[9].desc, "Fresh papaya juice with ice");
    normalMenu[9].price = 90;

    strcpy(normalMenu[10].name, "Lemon Rizz");
    strcpy(normalMenu[10].desc, "Premium zesty lemon refresher");
    normalMenu[10].price = 320;

    strcpy(normalMenu[11].name, "Moroccan Mint");
    strcpy(normalMenu[11].desc, "Refreshing traditional mint blend");
    normalMenu[11].price = 320;
}

void pauseAnyKey(void) {
    printf("\n  Press Enter to continue...");
    int c;
    while ((c = getchar()) != '\n');
    getchar();
}

int HasKeyword(const char *kw) {
    int i;
    for (i = 0; i < cartSize; i++) {
        char *n = cart[i].isTopping ? toppingIngredients[cart[i].index].name : baseIngredients[cart[i].index].name;
        if (strstr(n, kw) != NULL) {
            return 1;
        }
    }
    return 0;
}

int PortionsInCategory(int isTopping, int category) {
    int i;
    int total = 0;
    for (i = 0; i < cartSize; i++) {
        if (cart[i].isTopping == isTopping) {
            int cat = isTopping ? toppingIngredients[cart[i].index].category : baseIngredients[cart[i].index].category;
            if (cat == category) {
                total = total + cart[i].portions;
            }
        }
    }
    return total;
}

int CheckEWWarning(char *outMsg) {
    if ((HasKeyword("Lemonade") || HasKeyword("Lime")) && HasKeyword("Milk")) {
        strcpy(outMsg, "Uh oh, your milk's about to have a mid-life curdle-sis!");
        return 1;
    }
    if (HasKeyword("Pineapple") && (HasKeyword("Milk") || HasKeyword("Cream"))) {
        strcpy(outMsg, "Pineapple's about to bully your milk into cottage cheese!");
        return 1;
    }
    if (HasKeyword("Grapefruit") && (HasKeyword("Heavy Cream") || HasKeyword("Whole Milk") || HasKeyword("Condensed Milk"))) {
        strcpy(outMsg, "Grapefruit and cream are NOT besties, this gets sour fast!");
        return 1;
    }
    if ((HasKeyword("Matcha") || HasKeyword("Green Tea")) && (HasKeyword("Chocolate") || HasKeyword("Nutella"))) {
        strcpy(outMsg, "Poor matcha never stood a chance against all that chocolate!");
        return 1;
    }
    if ((HasKeyword("Mint") || HasKeyword("Peppermint")) && (HasKeyword("Mango") || HasKeyword("Papaya") || HasKeyword("Passionfruit"))) {
        strcpy(outMsg, "Congrats, you just invented tropical toothpaste!");
        return 1;
    }
    if (HasKeyword("Coconut Water") && (HasKeyword("Espresso") || HasKeyword("Milk"))) {
        strcpy(outMsg, "That coconut water is about to have the worst day of its life!");
        return 1;
    }
    if (HasKeyword("Sugarcane") && (HasKeyword("Chili") || HasKeyword("Cayenne"))) {
        strcpy(outMsg, "Sweet sugarcane meets spicy chili - plot twist incoming!");
        return 1;
    }
    if ((HasKeyword("Espresso") || HasKeyword("Coffee")) && HasKeyword("Watermelon")) {
        strcpy(outMsg, "Your coffee and watermelon are fighting, and nobody wins!");
        return 1;
    }
    if (HasKeyword("Matcha") && (HasKeyword("Lemon") || HasKeyword("Lime"))) {
        strcpy(outMsg, "Say bye to that pretty green - matcha's going swamp-brown!");
        return 1;
    }
    if (HasKeyword("Pepper") && (HasKeyword("Strawberry") || HasKeyword("Raspberry") || HasKeyword("Blueberry")) && HasKeyword("Milk")) {
        strcpy(outMsg, "Pepper, berries, AND milk? Your throat's staging a protest!");
        return 1;
    }
    if (HasKeyword("Grape Juice") && HasKeyword("Mint") && HasKeyword("Heavy Cream")) {
        strcpy(outMsg, "Grape juice, mint, and cream walk into a cup... it ends badly!");
        return 1;
    }
    if ((HasKeyword("Rosemary") || HasKeyword("Thyme") || HasKeyword("Sage")) && PortionsInCategory(1, 0) > 0) {
        strcpy(outMsg, "Savory herbs in a fruity drink? Bold. Weird. Let's see it!");
        return 1;
    }
    if (HasKeyword("Tonic") && HasKeyword("Heavy Cream")) {
        strcpy(outMsg, "Tonic water and heavy cream are throwing a chalky little party!");
        return 1;
    }
    if (HasKeyword("Jackfruit") && (HasKeyword("Soda") || HasKeyword("Sparkling") || HasKeyword("Club Soda"))) {
        strcpy(outMsg, "That jackfruit is about to get REALLY loud with all those bubbles!");
        return 1;
    }
    if (PortionsInCategory(1, 1) > 2) {
        strcpy(outMsg, "Sugar rush incoming - hope you brought your dancing shoes!");
        return 1;
    }
    if (PortionsInCategory(1, 2) > 2) {
        strcpy(outMsg, "Can't wait to see your cheeks go red!");
        return 1;
    }
    return 0;
}

int totalMl(void) {
    int t = 0;
    int i;
    for (i = 0; i < cartSize; i++) {
        if (cart[i].isTopping == 1) {
            t = t + toppingIngredients[cart[i].index].ml * cart[i].portions;
        } else {
            t = t + baseIngredients[cart[i].index].ml * cart[i].portions;
        }
    }
    return t;
}

int totalPrice(void) {
    int t = 0;
    int i;
    for (i = 0; i < cartSize; i++) {
        if (cart[i].isTopping == 1) {
            t = t + toppingIngredients[cart[i].index].price * cart[i].portions;
        } else {
            t = t + baseIngredients[cart[i].index].price * cart[i].portions;
        }
    }
    return t;
}

void showCart(void) {
    int i;
    char *n;
    int p;

    if (cartSize == 0) {
        printf("  (empty)\n");
        return;
    }

    for (i = 0; i < cartSize; i++) {
        if (cart[i].isTopping == 1) {
            n = toppingIngredients[cart[i].index].name;
            p = toppingIngredients[cart[i].index].price * cart[i].portions;
        } else {
            n = baseIngredients[cart[i].index].name;
            p = baseIngredients[cart[i].index].price * cart[i].portions;
        }
        printf("  %2d. %-34s x%d  %d Tk\n", i + 1, n, cart[i].portions, p);
    }
}

Color mcBaseA = {214, 234, 250, 255};
Color mcBaseB = {198, 222, 244, 255};
Color mcHoverA = {255, 214, 230, 255};
Color mcHoverB = {255, 198, 220, 255};
Color mcDisabledA = {225, 222, 226, 255};
Color mcDisabledB = {212, 208, 214, 255};
Color mcBorderDark = {150, 150, 190, 255};
Color mcHighlight = {255, 255, 255, 210};
Color mcShadowLine = {160, 150, 190, 255};
Color mcTextNormal = {90, 80, 110, 255};
Color mcTextHover = {150, 50, 90, 255};
Color mcTextShadow = {255, 255, 255, 180};
Color mcTextDisabled = {170, 130, 140, 255};

void DrawPixelFill(Rectangle r, Color colorA, Color colorB, int pixelSize) {
    int cols = (int)(r.width / pixelSize) + 1;
    int rows = (int)(r.height / pixelSize) + 1;
    int x, y;
    for (y = 0; y < rows; y++) {
        for (x = 0; x < cols; x++) {
            Color c = ((x + y) % 2 == 0) ? colorA : colorB;
            int px = (int)r.x + x * pixelSize;
            int py = (int)r.y + y * pixelSize;
            int w = pixelSize;
            int h = pixelSize;
            if (px + w > (int)(r.x + r.width)) w = (int)(r.x + r.width) - px;
            if (py + h > (int)(r.y + r.height)) h = (int)(r.y + r.height) - py;
            if (w > 0 && h > 0) {
                DrawRectangle(px, py, w, h, c);
            }
        }
    }
}

void DrawTextExBold(Font font, const char *text, Vector2 pos, float fontSize, float spacing, Color color) {
    DrawTextEx(font, text, (Vector2){pos.x + 1, pos.y}, fontSize, spacing, color);
    DrawTextEx(font, text, (Vector2){pos.x, pos.y + 1}, fontSize, spacing, color);
    DrawTextEx(font, text, (Vector2){pos.x + 1, pos.y + 1}, fontSize, spacing, color);
    DrawTextEx(font, text, pos, fontSize, spacing, color);
}

void DrawMCButtonBase(Rectangle r, int hovered) {
    Color colorA = hovered ? mcHoverA : mcBaseA;
    Color colorB = hovered ? mcHoverB : mcBaseB;

    DrawPixelFill(r, colorA, colorB, 6);
    DrawLine((int)r.x, (int)r.y, (int)(r.x + r.width), (int)r.y, mcHighlight);
    DrawLine((int)r.x, (int)r.y, (int)r.x, (int)(r.y + r.height), mcHighlight);
    DrawLine((int)(r.x + r.width), (int)r.y, (int)(r.x + r.width), (int)(r.y + r.height), mcShadowLine);
    DrawLine((int)r.x, (int)(r.y + r.height), (int)(r.x + r.width), (int)(r.y + r.height), mcShadowLine);
    DrawRectangleLinesEx(r, 3, mcBorderDark);
}

void DrawMCButtonDisabledBase(Rectangle r) {
    DrawPixelFill(r, mcDisabledA, mcDisabledB, 6);
    DrawRectangleLinesEx(r, 3, mcBorderDark);
}

void DrawMCButton(Rectangle r, const char *label, int hovered, int fontSize) {
    Color txt = hovered ? mcTextHover : mcTextNormal;
    Vector2 sz = MeasureTextEx(customFont, label, (float)fontSize, 1);
    float tx = r.x + (r.width - sz.x) / 2;
    float ty = r.y + (r.height - sz.y) / 2;

    DrawMCButtonBase(r, hovered);

    DrawTextExBold(customFont, label, (Vector2){tx + 2, ty + 2}, (float)fontSize, 1, mcTextShadow);
    DrawTextExBold(customFont, label, (Vector2){tx, ty}, (float)fontSize, 1, txt);
}

void DrawMCButtonDisabled(Rectangle r, const char *label, int fontSize) {
    Vector2 sz = MeasureTextEx(customFont, label, (float)fontSize, 1);
    float tx = r.x + (r.width - sz.x) / 2;
    float ty = r.y + (r.height - sz.y) / 2;

    DrawMCButtonDisabledBase(r);
    DrawTextExBold(customFont, label, (Vector2){tx, ty}, (float)fontSize, 1, mcTextDisabled);
}

Color GetIngredientColor(const char *name) {
    if (strstr(name, "Espresso") != NULL) return (Color){60, 40, 30, 255};
    if (strstr(name, "Coconut Jelly") != NULL) return (Color){235, 240, 236, 255};
    if (strstr(name, "Coffee Jelly") != NULL) return (Color){130, 90, 60, 255};
    if (strstr(name, "Boba") != NULL) return (Color){20, 20, 20, 255};
    if (strstr(name, "Basil Seed") != NULL) return (Color){15, 15, 15, 255};
    if (strstr(name, "Instant Coffee") != NULL) return (Color){110, 75, 45, 255};
    if (strstr(name, "Dark Chocolate") != NULL) return (Color){70, 40, 25, 255};
    if (strstr(name, "Crushed Ice Strawberry") != NULL) return (Color){250, 190, 205, 255};
    if (strstr(name, "Ice") != NULL) return (Color){225, 245, 250, 255};
    if (strstr(name, "Chopped Banana") != NULL) return (Color){250, 230, 150, 255};
    if (strstr(name, "Chopped Mango") != NULL) return (Color){255, 175, 60, 255};
    if (strstr(name, "Chopped Apple") != NULL) return (Color){200, 70, 60, 255};
    if (strstr(name, "Chocolate Syrup") != NULL) return (Color){90, 55, 35, 255};
    if (strstr(name, "Strawberry Syrup") != NULL) return (Color){210, 50, 80, 255};
    if (strstr(name, "Strawberry Jam") != NULL) return (Color){200, 40, 70, 255};
    if (strstr(name, "Mint") != NULL) return (Color){110, 180, 110, 255};
    if (strstr(name, "Blueberry") != NULL) return (Color){95, 78, 150, 255};
    if (strstr(name, "Pineapple") != NULL) return (Color){255, 205, 80, 255};
    if (strstr(name, "Papaya") != NULL) return (Color){255, 150, 80, 255};
    if (strstr(name, "Mango") != NULL) return (Color){255, 175, 60, 255};
    if (strstr(name, "Banana") != NULL) return (Color){250, 225, 140, 255};
    if (strstr(name, "Apple Juice") != NULL) return (Color){225, 215, 110, 255};
    if (strstr(name, "Sugarcane") != NULL) return (Color){220, 230, 150, 255};
    if (strstr(name, "Lemonade") != NULL) return (Color){255, 235, 140, 255};
    if (strstr(name, "Coconut Water") != NULL) return (Color){236, 236, 228, 255};
    if (strstr(name, "Chilled Water") != NULL) return (Color){215, 238, 250, 255};
    if (strstr(name, "Milk") != NULL) return (Color){248, 244, 230, 255};
    return (Color){210, 210, 210, 255};
}

int GetIngredientTexture(const char *name) {
    if (strstr(name, "Boba") != NULL) return 1;
    if (strstr(name, "Ice") != NULL) return 2;
    if (strstr(name, "Coconut Jelly") != NULL) return 3;
    if (strstr(name, "Coffee Jelly") != NULL) return 3;
    if (strstr(name, "Dark Chocolate") != NULL) return 4;
    if (strstr(name, "Instant Coffee") != NULL) return 4;
    if (strstr(name, "Basil Seed") != NULL) return 4;
    if (strstr(name, "Chopped") != NULL) return 5;
    return 0;
}

void DrawCupVisual(int cx, int topY, int height, int cupMl) {
    int topWidth = 220;
    int bottomWidth = 150;
    int sliceH = 6;
    int numSlices = height / sliceH;
    int i;
    Color cupColorA = (Color){235, 242, 252, 255};
    Color cupColorB = (Color){222, 232, 248, 255};
    Color outline = mcBorderDark;
    float fillFraction = (cupMl > 0) ? ((float)totalMl() / (float)cupMl) : 0;
    float liquidTopFrac;
    Color blend = (Color){225, 190, 160, 255};

    if (fillFraction < 0) fillFraction = 0;
    if (fillFraction > 1) fillFraction = 1;
    liquidTopFrac = 1.0f - fillFraction;

    if (cartSize > 0) {
        long rSum = 0, gSum = 0, bSum = 0;
        int wSum = 0;
        for (i = 0; i < cartSize; i++) {
            char *n;
            int ml;
            Color c;
            if (cart[i].isTopping) {
                n = toppingIngredients[cart[i].index].name;
                ml = toppingIngredients[cart[i].index].ml * cart[i].portions;
            } else {
                n = baseIngredients[cart[i].index].name;
                ml = baseIngredients[cart[i].index].ml * cart[i].portions;
            }
            c = GetIngredientColor(n);
            rSum = rSum + (long)c.r * ml;
            gSum = gSum + (long)c.g * ml;
            bSum = bSum + (long)c.b * ml;
            wSum = wSum + ml;
        }
        if (wSum > 0) {
            blend.r = (unsigned char)(rSum / wSum);
            blend.g = (unsigned char)(gSum / wSum);
            blend.b = (unsigned char)(bSum / wSum);
            blend.a = 255;
        }
    }

    for (i = 0; i < numSlices; i++) {
        float frac = (float)i / (numSlices - 1);
        int w = (int)(topWidth + (bottomWidth - topWidth) * frac);
        int y = topY + i * sliceH;
        int isLiquid = frac >= liquidTopFrac;
        Color c;
        if (isLiquid) {
            Color darker = { (unsigned char)(blend.r * 0.88f), (unsigned char)(blend.g * 0.88f), (unsigned char)(blend.b * 0.88f), 255 };
            c = ((i / 2) % 2 == 0) ? blend : darker;
        } else {
            c = ((i / 2) % 2 == 0) ? cupColorA : cupColorB;
        }
        DrawRectangle(cx - w / 2, y, w, sliceH + 1, c);
    }

    {
        Vector2 topLeft = {(float)(cx - topWidth / 2), (float)topY};
        Vector2 topRight = {(float)(cx + topWidth / 2), (float)topY};
        Vector2 botLeft = {(float)(cx - bottomWidth / 2), (float)(topY + height)};
        Vector2 botRight = {(float)(cx + bottomWidth / 2), (float)(topY + height)};
        DrawLineEx(topLeft, botLeft, 4, outline);
        DrawLineEx(topRight, botRight, 4, outline);
        DrawLineEx(botLeft, botRight, 4, outline);
    }

    DrawRectangleRounded((Rectangle){(float)(cx - topWidth / 2 - 8), (float)(topY - 16), (float)(topWidth + 16), 22}, 0.6f, 8, (Color){255, 255, 255, 255});
    DrawRectangleRoundedLinesEx((Rectangle){(float)(cx - topWidth / 2 - 8), (float)(topY - 16), (float)(topWidth + 16), 22}, 0.6f, 8, 3, outline);

    {
        Vector2 strawBottom = {(float)(cx - 6), (float)(topY - 8)};
        Vector2 strawTop = {(float)(cx + 38), (float)(topY - 80)};
        DrawLineEx(strawBottom, strawTop, 12, (Color){190, 220, 245, 255});
        DrawLineEx(strawBottom, strawTop, 12, Fade(outline, 0.5f));
        DrawLineEx((Vector2){strawBottom.x - 3, strawBottom.y}, (Vector2){strawTop.x - 3, strawTop.y}, 3, (Color){255, 255, 255, 200});
    }
}

void showNormalMenu(void) {
    struct NormalCartEntry cartNormal[MAX_NORMAL_CART_LINES];
    int cartNCount = 0;
    int i, j, id, sub, total;
    int screen = 0;
    int kbIndex = 0;
    int kbCol = 0;
    int kbRow = 0;
    int lastScreen = -1;
    int fadeAlpha = 0;
    int pendingDrinkId = 0;
    int addIce = 0;
    int addCaffeine = 0;
    int addWhip = 0;
    int addBoba = 0;
    char payName[10];

    Color bg = (Color){255, 240, 245, 255};
    Color textColor = (Color){90, 70, 70, 255};
    Color titleColor = (Color){150, 90, 100, 255};

    while (!WindowShouldClose()) {

        int clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        int enterPressed = IsKeyPressed(KEY_ENTER);
        int downPressed = IsKeyPressed(KEY_DOWN);
        int upPressed = IsKeyPressed(KEY_UP);
        int rightPressed = IsKeyPressed(KEY_RIGHT);
        int leftPressed = IsKeyPressed(KEY_LEFT);
        Vector2 mouse = GetMousePosition();

        if (screen != lastScreen) {
            fadeAlpha = 255;
            lastScreen = screen;
        }

        BeginDrawing();
        ClearBackground(bg);

        if (screen == 0) {

            int leftLen = NORMAL_MENU_COUNT;
            int rightLen = cartNCount + 2;
            int mouseOverRow;
            int hoveredRow;

            if (kbCol == 0 && kbRow >= leftLen) kbRow = leftLen - 1;
            if (kbCol == 1 && kbRow >= rightLen) kbRow = rightLen - 1;

            if (kbCol == 0) {
                if (downPressed) kbRow = (kbRow + 1) % leftLen;
                if (upPressed) kbRow = (kbRow - 1 + leftLen) % leftLen;
            } else {
                if (downPressed) kbRow = (kbRow + 1) % rightLen;
                if (upPressed) kbRow = (kbRow - 1 + rightLen) % rightLen;
            }
            if (rightPressed) {
                kbCol = 1;
                if (kbRow >= rightLen) kbRow = rightLen - 1;
            }
            if (leftPressed) {
                kbCol = 0;
                if (kbRow >= leftLen) kbRow = leftLen - 1;
            }

            DrawTextExBold(customFont, "Normal Menu - pick a drink", (Vector2){20, 15}, 41, 1, titleColor);

            for (i = 0; i < NORMAL_MENU_COUNT; i++) {
                Rectangle row = {20, 65 + i * 48, 620, 44};
                char label[100];

                mouseOverRow = CheckCollisionPointRec(mouse, row);
                hoveredRow = mouseOverRow || (kbCol == 0 && kbRow == i);

                sprintf(label, "%-28s %d Tk", normalMenu[i].name, normalMenu[i].price);
                DrawMCButton(row, label, hoveredRow, 26);

                if ((mouseOverRow && clicked) || (kbCol == 0 && kbRow == i && enterPressed)) {
                    pendingDrinkId = i;
                    addIce = 0;
                    addCaffeine = 0;
                    addWhip = 0;
                    addBoba = 0;
                    screen = 3;
                    kbIndex = 0;
                }
            }

            DrawTextExBold(customFont, "Your Cart:", (Vector2){680, 15}, 36, 1, titleColor);
            total = 0;

            for (i = 0; i < cartNCount; i++) {
                char line[120];
                char tags[40];
                Rectangle minusBtn = {920, 58 + i * 44, 46, 32};
                int mouseOverMinus = CheckCollisionPointRec(mouse, minusBtn);
                int hoveredMinus = mouseOverMinus || (kbCol == 1 && kbRow == i);
                int unitPrice;

                id = cartNormal[i].id;
                unitPrice = normalMenu[id].price;
                tags[0] = '\0';
                if (cartNormal[i].ice) { unitPrice += 30; strcat(tags, "+Ice "); }
                if (cartNormal[i].caffeine) { unitPrice += 60; strcat(tags, "+Caf "); }
                if (cartNormal[i].whip) { unitPrice += 90; strcat(tags, "+Whip "); }
                if (cartNormal[i].boba) { unitPrice += 100; strcat(tags, "+Boba "); }

                sub = unitPrice * cartNormal[i].qty;
                total = total + sub;

                sprintf(line, "%dx %s %s= %d Tk", cartNormal[i].qty, normalMenu[id].name, tags, sub);
                DrawTextExBold(customFont, line, (Vector2){680, 60 + i * 44}, 18, 1, textColor);

                DrawMCButton(minusBtn, "-", hoveredMinus, 31);

                if ((mouseOverMinus && clicked) || (kbCol == 1 && kbRow == i && enterPressed)) {
                    cartNormal[i].qty = cartNormal[i].qty - 1;
                    if (cartNormal[i].qty <= 0) {
                        for (j = i; j < cartNCount - 1; j++) {
                            cartNormal[j] = cartNormal[j + 1];
                        }
                        cartNCount = cartNCount - 1;
                    }
                }
            }

            {
                char totalLine[50];
                Rectangle checkoutBtn = {680, 560, 320, 65};
                Rectangle backBtn = {680, 635, 320, 65};
                int checkoutRow = cartNCount;
                int backRow = cartNCount + 1;
                int mouseOverCheckout = CheckCollisionPointRec(mouse, checkoutBtn);
                int mouseOverBack = CheckCollisionPointRec(mouse, backBtn);
                int hoveredCheckout = mouseOverCheckout || (kbCol == 1 && kbRow == checkoutRow);
                int hoveredBack = mouseOverBack || (kbCol == 1 && kbRow == backRow);

                sprintf(totalLine, "Total: %d Tk", total);
                DrawTextExBold(customFont, totalLine, (Vector2){680, 500}, 34, 1, titleColor);

                DrawMCButton(checkoutBtn, "Checkout", hoveredCheckout, 37);
                DrawMCButton(backBtn, "Back to Main Menu", hoveredBack, 29);

                if (((mouseOverCheckout && clicked) || (kbCol == 1 && kbRow == checkoutRow && enterPressed)) && cartNCount > 0) {
                    screen = 1;
                    kbIndex = 0;
                }
                if ((mouseOverBack && clicked) || (kbCol == 1 && kbRow == backRow && enterPressed)) {
                    EndDrawing();
                    return;
                }
            }

        } else if (screen == 3) {

            Rectangle iceBtn   = {325, 220, 400, 65};
            Rectangle cafBtn   = {325, 295, 400, 65};
            Rectangle whipBtn  = {325, 370, 400, 65};
            Rectangle bobaBtn  = {325, 445, 400, 65};
            Rectangle confirmBtn = {325, 550, 400, 70};

            int mouseOverIce = CheckCollisionPointRec(mouse, iceBtn);
            int mouseOverCaf = CheckCollisionPointRec(mouse, cafBtn);
            int mouseOverWhip = CheckCollisionPointRec(mouse, whipBtn);
            int mouseOverBoba = CheckCollisionPointRec(mouse, bobaBtn);
            int mouseOverConfirm = CheckCollisionPointRec(mouse, confirmBtn);

            char hd[100];
            Vector2 hdSize;
            char iceLbl[60], cafLbl[60], whipLbl[60], bobaLbl[60];

            if (downPressed || rightPressed) kbIndex = (kbIndex + 1) % 5;
            if (upPressed || leftPressed) kbIndex = (kbIndex - 1 + 5) % 5;

            sprintf(hd, "Add-ons for %s?", normalMenu[pendingDrinkId].name);
            hdSize = MeasureTextEx(customFont, hd, 34, 1);
            DrawTextExBold(customFont, hd, (Vector2){(1050 - hdSize.x) / 2, 130}, 34, 1, titleColor);

            sprintf(iceLbl, "[%s] Extra Ice (+30 Tk)", addIce ? "x" : " ");
            sprintf(cafLbl, "[%s] Caffeine (+60 Tk)", addCaffeine ? "x" : " ");
            sprintf(whipLbl, "[%s] Whipped Cream (+90 Tk)", addWhip ? "x" : " ");
            sprintf(bobaLbl, "[%s] Boba (+100 Tk)", addBoba ? "x" : " ");

            DrawMCButton(iceBtn, iceLbl, mouseOverIce || kbIndex == 0, 24);
            DrawMCButton(cafBtn, cafLbl, mouseOverCaf || kbIndex == 1, 24);
            DrawMCButton(whipBtn, whipLbl, mouseOverWhip || kbIndex == 2, 24);
            DrawMCButton(bobaBtn, bobaLbl, mouseOverBoba || kbIndex == 3, 24);
            DrawMCButton(confirmBtn, "Confirm", mouseOverConfirm || kbIndex == 4, 28);

            if ((mouseOverIce && clicked) || (kbIndex == 0 && enterPressed)) addIce = !addIce;
            if ((mouseOverCaf && clicked) || (kbIndex == 1 && enterPressed)) addCaffeine = !addCaffeine;
            if ((mouseOverWhip && clicked) || (kbIndex == 2 && enterPressed)) addWhip = !addWhip;
            if ((mouseOverBoba && clicked) || (kbIndex == 3 && enterPressed)) addBoba = !addBoba;

            if ((mouseOverConfirm && clicked) || (kbIndex == 4 && enterPressed)) {
                int found = 0;
                for (j = 0; j < cartNCount; j++) {
                    if (cartNormal[j].id == pendingDrinkId &&
                        cartNormal[j].ice == addIce &&
                        cartNormal[j].caffeine == addCaffeine &&
                        cartNormal[j].whip == addWhip &&
                        cartNormal[j].boba == addBoba) {
                        cartNormal[j].qty = cartNormal[j].qty + 1;
                        found = 1;
                        break;
                    }
                }
                if (!found && cartNCount < MAX_NORMAL_CART_LINES) {
                    cartNormal[cartNCount].id = pendingDrinkId;
                    cartNormal[cartNCount].qty = 1;
                    cartNormal[cartNCount].ice = addIce;
                    cartNormal[cartNCount].caffeine = addCaffeine;
                    cartNormal[cartNCount].whip = addWhip;
                    cartNormal[cartNCount].boba = addBoba;
                    cartNCount = cartNCount + 1;
                }
                screen = 0;
            }

        } else if (screen == 1) {

            Rectangle cashBtn  = {330, 260, 340, 75};
            Rectangle bkashBtn = {330, 350, 340, 75};
            Rectangle nagadBtn = {330, 440, 340, 75};
            int mouseOverCash  = CheckCollisionPointRec(mouse, cashBtn);
            int mouseOverBkash = CheckCollisionPointRec(mouse, bkashBtn);
            int mouseOverNagad = CheckCollisionPointRec(mouse, nagadBtn);

            if (downPressed || rightPressed) kbIndex = (kbIndex + 1) % 3;
            if (upPressed || leftPressed) kbIndex = (kbIndex - 1 + 3) % 3;

            DrawTextExBold(customFont, "Select payment method", (Vector2){300, 150}, 43, 1, titleColor);

            DrawMCButton(cashBtn, "Cash", mouseOverCash || kbIndex == 0, 41);
            DrawMCButton(bkashBtn, "bKash", mouseOverBkash || kbIndex == 1, 41);
            DrawMCButton(nagadBtn, "Nagad", mouseOverNagad || kbIndex == 2, 41);

            if ((clicked && mouseOverCash) || (kbIndex == 0 && enterPressed)) {
                strcpy(payName, "Cash");
                screen = 2;
                kbIndex = 0;
            }
            if ((clicked && mouseOverBkash) || (kbIndex == 1 && enterPressed)) {
                strcpy(payName, "bKash");
                screen = 2;
                kbIndex = 0;
            }
            if ((clicked && mouseOverNagad) || (kbIndex == 2 && enterPressed)) {
                strcpy(payName, "Nagad");
                screen = 2;
                kbIndex = 0;
            }

        } else {

            char line2[80];
            char line3[50];
            Rectangle okBtn = {400, 440, 220, 75};
            int mouseOverOk = CheckCollisionPointRec(mouse, okBtn);

            total = 0;
            for (i = 0; i < cartNCount; i++) {
                id = cartNormal[i].id;
                int unitPrice = normalMenu[id].price;
                if (cartNormal[i].ice) unitPrice += 30;
                if (cartNormal[i].caffeine) unitPrice += 60;
                if (cartNormal[i].whip) unitPrice += 90;
                if (cartNormal[i].boba) unitPrice += 100;
                total = total + unitPrice * cartNormal[i].qty;
            }

            DrawTextExBold(customFont, "Yay! Can't wait for the drink! ^_^", (Vector2){190, 210}, 38, 1, titleColor);

            sprintf(line2, "Payment via %s confirmed.", payName);
            DrawTextExBold(customFont, line2, (Vector2){260, 280}, 31, 1, textColor);

            sprintf(line3, "Total paid: %d Tk", total);
            DrawTextExBold(customFont, line3, (Vector2){330, 325}, 31, 1, textColor);

            DrawMCButton(okBtn, "OK", mouseOverOk || kbIndex == 0, 41);

            if ((mouseOverOk && clicked) || enterPressed) {
                EndDrawing();
                return;
            }
        }

        if (fadeAlpha > 0) {
            DrawRectangle(0, 0, 1050, 740, Fade(bg, (float)fadeAlpha / 255.0f));
            fadeAlpha = fadeAlpha - 30;
            if (fadeAlpha < 0) fadeAlpha = 0;
        }

        EndDrawing();
    }

    exit(0);
}
void showCustomMenu(void) {
    int budget = 0;
    int cupChoice = 0;
    int cupMl = 0;
    int i, j;
    int screen;
    int toppingPage;
    int currentCat;
    int pendingIsTopping;
    int pendingIndex;
    int pendingPortions;
    int warningType;
    char warningMsg[150];
    int kbIndex;
    int kbCol;
    int kbRow;
    int lastScreen = -1;
    int fadeAlpha = 0;
    char numBuffer[12];
    char payName[10];
    struct Ingredient *pendingList;

    Color bg = (Color){255, 240, 245, 255};
    Color titleColor = (Color){150, 90, 100, 255};
    Color textColor = (Color){90, 70, 70, 255};

    cartSize = 0;
    cupMl = 0;
    screen = 0;
    toppingPage = 0;
    currentCat = 0;
    numBuffer[0] = '\0';
    warningType = 0;
    kbIndex = 0;
    kbCol = 0;
    kbRow = 0;

    while (!WindowShouldClose()) {

        Vector2 mouse = GetMousePosition();
        int clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        int enterPressed = IsKeyPressed(KEY_ENTER);
        int downPressed = IsKeyPressed(KEY_DOWN);
        int upPressed = IsKeyPressed(KEY_UP);
        int rightPressed = IsKeyPressed(KEY_RIGHT);
        int leftPressed = IsKeyPressed(KEY_LEFT);

        if (screen != lastScreen) {
            fadeAlpha = 255;
            lastScreen = screen;
        }

        BeginDrawing();
        ClearBackground(bg);

        if (screen == 0 || screen == 5) {

            int slots = 12;
            int gridCols = 3;
            int gridRows = 4;
            int gridRow = kbIndex / gridCols;
            int gridCol = kbIndex % gridCols;
            int isPortions = (screen == 5);
            int maxDigits = isPortions ? 3 : 6;
            int gx = 338;

            if (downPressed) gridRow = (gridRow + 1) % gridRows;
            if (upPressed) gridRow = (gridRow - 1 + gridRows) % gridRows;
            if (rightPressed) gridCol = (gridCol + 1) % gridCols;
            if (leftPressed) gridCol = (gridCol - 1 + gridCols) % gridCols;
            kbIndex = gridRow * gridCols + gridCol;
            if (kbIndex >= slots) kbIndex = slots - 1;

            if (isPortions) {
                char hd[100];
                Vector2 hdSize;
                sprintf(hd, "How many portions of %s?", pendingList[pendingIndex].name);
                hdSize = MeasureTextEx(customFont, hd, 36, 1);
                DrawTextExBold(customFont, hd, (Vector2){(1050 - hdSize.x) / 2, 20}, 36, 1, titleColor);
            } else {
                const char *hd2 = "Hi! What's your budget?";
                Vector2 hdSize = MeasureTextEx(customFont, hd2, 41, 1);
                DrawTextExBold(customFont, hd2, (Vector2){(1050 - hdSize.x) / 2, 20}, 41, 1, titleColor);
            }

            {
                char numDisplay[20];
                Vector2 numSize;
                if (numBuffer[0]) {
                    if (isPortions) {
                        strcpy(numDisplay, numBuffer);
                    } else {
                        sprintf(numDisplay, "%s Tk", numBuffer);
                    }
                } else {
                    strcpy(numDisplay, isPortions ? "0" : "0 Tk");
                }
                numSize = MeasureTextEx(customFont, numDisplay, 67, 1);
                DrawTextExBold(customFont, numDisplay, (Vector2){(1050 - numSize.x) / 2, 90}, 67, 1, textColor);
            }

            for (i = 0; i < 9; i++) {
                Rectangle r = {(float)(gx + (i % 3) * 130), 180 + (i / 3) * 95, 115, 82};
                int mouseOver = CheckCollisionPointRec(mouse, r);
                int hovered = mouseOver || (kbIndex == i);
                char label[2] = { (char)('1' + i), '\0' };
                DrawMCButton(r, label, hovered, 46);
                if ((mouseOver && clicked && strlen(numBuffer) < maxDigits) ||
                    (kbIndex == i && enterPressed && strlen(numBuffer) < maxDigits)) {
                    strcat(numBuffer, label);
                }
            }

            {
                Rectangle zeroR = {(float)gx, 465, 115, 82};
                Rectangle delR = {(float)(gx + 130), 465, 115, 82};
                Rectangle okR = {(float)(gx + 260), 465, 195, 82};
                int mouseOverZero = CheckCollisionPointRec(mouse, zeroR);
                int mouseOverDel = CheckCollisionPointRec(mouse, delR);
                int mouseOverOk = CheckCollisionPointRec(mouse, okR);

                DrawMCButton(zeroR, "0", mouseOverZero || kbIndex == 9, 46);
                DrawMCButton(delR, "Del", mouseOverDel || kbIndex == 10, 37);
                DrawMCButton(okR, "Confirm", mouseOverOk || kbIndex == 11, 37);

                if (((mouseOverZero && clicked) || (kbIndex == 9 && enterPressed)) && strlen(numBuffer) < maxDigits) {
                    strcat(numBuffer, "0");
                }
                if (((mouseOverDel && clicked) || (kbIndex == 10 && enterPressed)) && strlen(numBuffer) > 0) {
                    numBuffer[strlen(numBuffer) - 1] = '\0';
                }

                if (isPortions) {
                    Rectangle cancelR = {(float)(gx + 260), 560, 195, 65};
                    int mouseOverCancel = CheckCollisionPointRec(mouse, cancelR);
                    DrawMCButton(cancelR, "Cancel", mouseOverCancel, 35);
                    if (mouseOverCancel && clicked) {
                        numBuffer[0] = '\0';
                        screen = pendingIsTopping ? 4 : 3;
                        kbIndex = 0;
                    }
                }

                if (((mouseOverOk && clicked) || (kbIndex == 11 && enterPressed)) && strlen(numBuffer) > 0) {
                    if (!isPortions) {
                        budget = atoi(numBuffer);
                        numBuffer[0] = '\0';
                        screen = 1;
                        kbIndex = 0;
                    } else {
                        int portions = atoi(numBuffer);
                        struct Ingredient *ch = &pendingList[pendingIndex];
                        int fitsMl = ch->ml * portions <= cupMl - totalMl();
                        int fitsPrice = ch->price * portions <= budget - totalPrice();

                        pendingPortions = portions;
                        numBuffer[0] = '\0';

                        if (portions < 1 || !fitsMl || !fitsPrice) {
                            screen = pendingIsTopping ? 4 : 3;
                            kbIndex = 0;
                        } else {
                            int hasWarn = 0;

                            if (cartSize < MAX_INGREDIENTS) {
                                cart[cartSize].index = pendingIndex;
                                cart[cartSize].isTopping = pendingIsTopping;
                                cart[cartSize].portions = portions;
                                cartSize = cartSize + 1;

                                hasWarn = CheckEWWarning(warningMsg);

                                cartSize = cartSize - 1;
                            }
                            warningType = hasWarn;

                            if (warningType != 0) {
                                screen = 6;
                                kbIndex = 0;
                            } else {
                                int merged = 0;
                                for (j = 0; j < cartSize; j++) {
                                    if (cart[j].isTopping == pendingIsTopping && cart[j].index == pendingIndex) {
                                        cart[j].portions = cart[j].portions + portions;
                                        merged = 1;
                                        break;
                                    }
                                }
                                if (!merged && cartSize < MAX_INGREDIENTS) {
                                    cart[cartSize].index = pendingIndex;
                                    cart[cartSize].isTopping = pendingIsTopping;
                                    cart[cartSize].portions = portions;
                                    cartSize = cartSize + 1;
                                }
                                screen = 2;
                                kbIndex = 0;
                                kbCol = 0;
                                kbRow = 0;
                            }
                        }
                    }
                }
            }

        } else if (screen == 1) {

            char line[80];

            if (downPressed || rightPressed) kbIndex = (kbIndex + 1) % 4;
            if (upPressed || leftPressed) kbIndex = (kbIndex - 1 + 4) % 4;

            sprintf(line, "With %d Tk, pick your cup:", budget);
            DrawTextExBold(customFont, line, (Vector2){40, 30}, 41, 1, titleColor);

            for (i = 0; i < 4; i++) {
                Rectangle r = {40, 100 + i * 95, 480, 80};
                int mouseOver = CheckCollisionPointRec(mouse, r);
                int hovered = mouseOver || (kbIndex == i);
                char lbl[60];
                sprintf(lbl, "%s (%d ml)", cupSizes[i].name, cupSizes[i].ml);
                DrawMCButton(r, lbl, hovered, 41);
                if ((mouseOver && clicked) || (kbIndex == i && enterPressed)) {
                    cupChoice = i + 1;
                    cupMl = cupSizes[i].ml;
                    screen = 2;
                    kbIndex = 0;
                    kbCol = 0;
                    kbRow = 0;
                }
            }

        } else if (screen == 2) {

            char line1[80];
            char line2[100];

            int btnW = 260;
            int gap = 20;
            int leftX = (1050 - (2 * btnW + gap)) / 2;
            int midX = (1050 - btnW) / 2;

            Rectangle addBaseBtn = {(float)leftX, 500, (float)btnW, 65};
            Rectangle addTopBtn  = {(float)(leftX + btnW + gap), 500, (float)btnW, 65};
            Rectangle undoBtn    = {(float)midX, 575, (float)btnW, 65};
            Rectangle doneBtn    = {(float)leftX, 650, (float)btnW, 65};
            Rectangle cancelBtn  = {(float)(leftX + btnW + gap), 650, (float)btnW, 65};

            int mouseOverAddBase = CheckCollisionPointRec(mouse, addBaseBtn);
            int mouseOverAddTop = CheckCollisionPointRec(mouse, addTopBtn);
            int mouseOverUndo = CheckCollisionPointRec(mouse, undoBtn);
            int mouseOverDone = CheckCollisionPointRec(mouse, doneBtn);
            int mouseOverCancel = CheckCollisionPointRec(mouse, cancelBtn);

            if (downPressed) kbRow = (kbRow + 1) % 3;
            if (upPressed) kbRow = (kbRow - 1 + 3) % 3;
            if ((rightPressed || leftPressed) && kbRow != 1) kbCol = 1 - kbCol;

            {
                int hoveredAddBase = mouseOverAddBase || (kbRow == 0 && kbCol == 0);
                int hoveredAddTop = mouseOverAddTop || (kbRow == 0 && kbCol == 1);
                int hoveredUndo = mouseOverUndo || (kbRow == 1);
                int hoveredDone = mouseOverDone || (kbRow == 2 && kbCol == 0);
                int hoveredCancel = mouseOverCancel || (kbRow == 2 && kbCol == 1);

                Vector2 s1, s2;

                sprintf(line1, "Cup: %d ml | Filled: %d ml", cupMl, totalMl());
                sprintf(line2, "Budget left: %d Tk | Space left: %d ml", budget - totalPrice(), cupMl - totalMl());
                s1 = MeasureTextEx(customFont, line1, 27, 1);
                s2 = MeasureTextEx(customFont, line2, 27, 1);
                DrawTextExBold(customFont, line1, (Vector2){(1050 - s1.x) / 2, 15}, 27, 1, titleColor);
                DrawTextExBold(customFont, line2, (Vector2){(1050 - s2.x) / 2, 48}, 27, 1, titleColor);

                DrawCupVisual(350, 220, 240, cupMl);

                for (i = 0; i < cartSize; i++) {
                    char nline[100];
                    char *n;
                    int p;
                    int ml;
                    if (cart[i].isTopping) {
                        n = toppingIngredients[cart[i].index].name;
                        p = toppingIngredients[cart[i].index].price * cart[i].portions;
                        ml = toppingIngredients[cart[i].index].ml * cart[i].portions;
                    } else {
                        n = baseIngredients[cart[i].index].name;
                        p = baseIngredients[cart[i].index].price * cart[i].portions;
                        ml = baseIngredients[cart[i].index].ml * cart[i].portions;
                    }
                    sprintf(nline, "x%d %s  %dml %dTk", cart[i].portions, n, ml, p);
                    DrawTextExBold(customFont, nline, (Vector2){650, 135 + i * 26}, 18, 1, textColor);
                }

                DrawMCButton(addBaseBtn, "Add Base", hoveredAddBase, 31);
                DrawMCButton(addTopBtn, "Add Toppings", hoveredAddTop, 31);
                DrawMCButton(undoBtn, "Undo Last", hoveredUndo, 31);
                DrawMCButton(doneBtn, "Checkout", hoveredDone, 31);
                DrawMCButton(cancelBtn, "Cancel", hoveredCancel, 31);

                if ((mouseOverAddBase && clicked) || (kbRow == 0 && kbCol == 0 && enterPressed)) {
                    screen = 10;
                    kbIndex = 0;
                }
                if ((mouseOverAddTop && clicked) || (kbRow == 0 && kbCol == 1 && enterPressed)) {
                    screen = 11;
                    kbIndex = 0;
                }
                if ((mouseOverUndo && clicked) || (kbRow == 1 && enterPressed)) {
                    if (cartSize > 0) {
                        cartSize = cartSize - 1;
                    }
                }
                if (((mouseOverDone && clicked) || (kbRow == 2 && kbCol == 0 && enterPressed)) && cartSize > 0) {
                    screen = 8;
                    kbIndex = 0;
                }
                if ((mouseOverCancel && clicked) || (kbRow == 2 && kbCol == 1 && enterPressed)) {
                    if (cartSize > 0) {
                        screen = 7;
                        kbIndex = 0;
                    } else {
                        EndDrawing();
                        return;
                    }
                }
            }

        } else if (screen == 10 || screen == 11) {

            int isTop = (screen == 11);
            int catCount = isTop ? TOPPING_CATS : BASE_CATS;
            int slots = catCount + 1;
            const char **names = isTop ? toppingCatNames : baseCatNames;

            if (downPressed || rightPressed) kbIndex = (kbIndex + 1) % slots;
            if (upPressed || leftPressed) kbIndex = (kbIndex - 1 + slots) % slots;

            {
                const char *hd = isTop ? "Pick a Topping Category" : "Pick a Base Category";
                Vector2 hdSize = MeasureTextEx(customFont, hd, 34, 1);
                DrawTextExBold(customFont, hd, (Vector2){(1050 - hdSize.x) / 2, 40}, 34, 1, titleColor);
            }

            for (i = 0; i < catCount; i++) {
                Rectangle r = {175, 110 + i * 75, 700, 62};
                int mouseOver = CheckCollisionPointRec(mouse, r);
                int hovered = mouseOver || kbIndex == i;
                DrawMCButton(r, names[i], hovered, 26);
                if ((mouseOver && clicked) || (kbIndex == i && enterPressed)) {
                    pendingIsTopping = isTop;
                    pendingList = isTop ? toppingIngredients : baseIngredients;
                    currentCat = i;
                    toppingPage = 0;
                    screen = 3;
                    kbCol = 0;
                    kbRow = 0;
                }
            }

            {
                Rectangle backBtn = {345, 110 + catCount * 75 + 10, 360, 60};
                int mouseOverBack = CheckCollisionPointRec(mouse, backBtn);
                int backSlot = catCount;
                DrawMCButton(backBtn, "Back", mouseOverBack || kbIndex == backSlot, 26);
                if ((mouseOverBack && clicked) || (kbIndex == backSlot && enterPressed)) {
                    screen = 2;
                    kbIndex = 0;
                }
            }

        } else if (screen == 3) {

            int isTop = pendingIsTopping;
            struct Ingredient *list = pendingList;
            int catCount = isTop ? toppingCatCount[currentCat] : baseCatCount[currentCat];
            int catStart = isTop ? toppingCatStart[currentCat] : baseCatStart[currentCat];
            int totalPages = (catCount + PAGE_SIZE - 1) / PAGE_SIZE;
            int listStart = catStart + toppingPage * PAGE_SIZE;
            int listEnd = listStart + PAGE_SIZE;
            int remaining = cupMl - totalMl();
            int remainingBudget = budget - totalPrice();
            int rowCount;
            int sideLen;
            char hd[100];

            if (listEnd > catStart + catCount) listEnd = catStart + catCount;

            rowCount = listEnd - listStart;
            sideLen = (totalPages > 1 ? 2 : 0) + 1;

            if (kbCol == 0 && kbRow >= rowCount) kbRow = rowCount - 1;
            if (kbCol == 1 && kbRow >= sideLen) kbRow = sideLen - 1;

            if (kbCol == 0) {
                int tries;

                if (downPressed) {
                    tries = 0;
                    do {
                        kbRow = (kbRow + 1) % rowCount;
                        tries = tries + 1;
                    } while (!(list[listStart + kbRow].price <= remainingBudget && list[listStart + kbRow].ml <= remaining) && tries < rowCount);
                }
                if (upPressed) {
                    tries = 0;
                    do {
                        kbRow = (kbRow - 1 + rowCount) % rowCount;
                        tries = tries + 1;
                    } while (!(list[listStart + kbRow].price <= remainingBudget && list[listStart + kbRow].ml <= remaining) && tries < rowCount);
                }

                tries = 0;
                while (!(list[listStart + kbRow].price <= remainingBudget && list[listStart + kbRow].ml <= remaining) && tries < rowCount) {
                    kbRow = (kbRow + 1) % rowCount;
                    tries = tries + 1;
                }
            } else {
                if (downPressed) kbRow = (kbRow + 1) % sideLen;
                if (upPressed) kbRow = (kbRow - 1 + sideLen) % sideLen;
            }
            if (rightPressed) {
                kbCol = 1;
                if (kbRow >= sideLen) kbRow = sideLen - 1;
            }
            if (leftPressed) {
                int tries = 0;
                kbCol = 0;
                if (kbRow >= rowCount) kbRow = rowCount - 1;
                while (!(list[listStart + kbRow].price <= remainingBudget && list[listStart + kbRow].ml <= remaining) && tries < rowCount) {
                    kbRow = (kbRow + 1) % rowCount;
                    tries = tries + 1;
                }
            }

            sprintf(hd, "%s - Page %d/%d - Space:%dml Budget:%dTk",
                isTop ? toppingCatNames[currentCat] : baseCatNames[currentCat],
                toppingPage + 1, totalPages, remaining, remainingBudget);
            {
                Vector2 hdSize = MeasureTextEx(customFont, hd, 24, 1);
                DrawTextExBold(customFont, hd, (Vector2){(1050 - hdSize.x) / 2, 15}, 24, 1, titleColor);
            }

            for (i = listStart; i < listEnd; i++) {
                Rectangle r = {80, 60 + (i - listStart) * 46, 700, 40};
                int mouseOver = CheckCollisionPointRec(mouse, r);
                int slotIdx = i - listStart;
                int hovered = mouseOver || (kbCol == 0 && kbRow == slotIdx);
                int afford = (list[i].price <= remainingBudget && list[i].ml <= remaining);
                char lbl[100];
                sprintf(lbl, "%s  %d Tk  %d ml", list[i].name, list[i].price, list[i].ml);

                if (afford) {
                    DrawMCButton(r, lbl, hovered, 22);
                } else {
                    DrawMCButtonDisabled(r, lbl, 22);
                }

                if (afford && ((mouseOver && clicked) || (kbCol == 0 && kbRow == slotIdx && enterPressed))) {
                    pendingIndex = i;
                    numBuffer[0] = '\0';
                    screen = 5;
                    kbIndex = 0;
                }
            }

            if (totalPages > 1) {
                Rectangle prevBtn = {800, 60, 130, 50};
                Rectangle nextBtn = {800, 120, 130, 50};
                int mouseOverPrev = CheckCollisionPointRec(mouse, prevBtn);
                int mouseOverNext = CheckCollisionPointRec(mouse, nextBtn);

                DrawMCButton(prevBtn, "Prev", mouseOverPrev || (kbCol == 1 && kbRow == 0), 22);
                DrawMCButton(nextBtn, "Next", mouseOverNext || (kbCol == 1 && kbRow == 1), 22);

                if ((mouseOverPrev && clicked) || (kbCol == 1 && kbRow == 0 && enterPressed)) {
                    toppingPage = (toppingPage - 1 + totalPages) % totalPages;
                    kbRow = 0;
                }
                if ((mouseOverNext && clicked) || (kbCol == 1 && kbRow == 1 && enterPressed)) {
                    toppingPage = (toppingPage + 1) % totalPages;
                    kbRow = 0;
                }
            }

            {
                Rectangle backBtn = {800, 590, 170, 60};
                int mouseOverBack = CheckCollisionPointRec(mouse, backBtn);
                int backRow = sideLen - 1;
                DrawMCButton(backBtn, "Back", mouseOverBack || (kbCol == 1 && kbRow == backRow), 24);
                if ((mouseOverBack && clicked) || (kbCol == 1 && kbRow == backRow && enterPressed)) {
                    screen = isTop ? 11 : 10;
                    kbIndex = 0;
                    kbCol = 0;
                    kbRow = 0;
                }
            }

        } else if (screen == 6) {

            Rectangle yesBtn = {200, 320, 280, 75};
            Rectangle noBtn  = {560, 320, 280, 75};
            int mouseOverYes = CheckCollisionPointRec(mouse, yesBtn);
            int mouseOverNo = CheckCollisionPointRec(mouse, noBtn);

            if (rightPressed) kbIndex = (kbIndex + 1) % 2;
            if (leftPressed) kbIndex = (kbIndex - 1 + 2) % 2;

            {
                Vector2 msgSize = MeasureTextEx(customFont, warningMsg, 32, 1);
                DrawTextExBold(customFont, warningMsg, (Vector2){(1050 - msgSize.x) / 2, 200}, 32, 1, titleColor);
            }

            DrawMCButton(yesBtn, "Proceed anyway", mouseOverYes || kbIndex == 0, 26);
            DrawMCButton(noBtn, "No, cancel", mouseOverNo || kbIndex == 1, 26);

            if ((mouseOverYes && clicked) || (kbIndex == 0 && enterPressed)) {
                int merged = 0;
                for (j = 0; j < cartSize; j++) {
                    if (cart[j].isTopping == pendingIsTopping && cart[j].index == pendingIndex) {
                        cart[j].portions = cart[j].portions + pendingPortions;
                        merged = 1;
                        break;
                    }
                }
                if (!merged && cartSize < MAX_INGREDIENTS) {
                    cart[cartSize].index = pendingIndex;
                    cart[cartSize].isTopping = pendingIsTopping;
                    cart[cartSize].portions = pendingPortions;
                    cartSize = cartSize + 1;
                }
                screen = 2;
                kbIndex = 0;
                kbCol = 0;
                kbRow = 0;
            }
            if ((mouseOverNo && clicked) || (kbIndex == 1 && enterPressed)) {
                screen = 2;
                kbIndex = 0;
                kbCol = 0;
                kbRow = 0;
            }

        } else if (screen == 7) {

            Rectangle yesBtn = {230, 360, 240, 75};
            Rectangle noBtn  = {530, 360, 240, 75};
            int mouseOverYes = CheckCollisionPointRec(mouse, yesBtn);
            int mouseOverNo = CheckCollisionPointRec(mouse, noBtn);

            if (rightPressed) kbIndex = (kbIndex + 1) % 2;
            if (leftPressed) kbIndex = (kbIndex - 1 + 2) % 2;

            {
                const char *msg = "Are you sure? Everything will be lost.";
                Vector2 msgSize = MeasureTextEx(customFont, msg, 40, 1);
                DrawTextExBold(customFont, msg, (Vector2){(1050 - msgSize.x) / 2, 250}, 40, 1, titleColor);
            }

            DrawMCButton(yesBtn, "Yes, go back", mouseOverYes || kbIndex == 0, 31);
            DrawMCButton(noBtn, "No, stay", mouseOverNo || kbIndex == 1, 31);

            if ((mouseOverYes && clicked) || (kbIndex == 0 && enterPressed)) {
                EndDrawing();
                return;
            }
            if ((mouseOverNo && clicked) || (kbIndex == 1 && enterPressed)) {
                screen = 2;
                kbIndex = 0;
                kbCol = 0;
                kbRow = 0;
            }

        } else if (screen == 8) {

            Rectangle cashBtn  = {330, 260, 340, 75};
            Rectangle bkashBtn = {330, 350, 340, 75};
            Rectangle nagadBtn = {330, 440, 340, 75};
            int mouseOverCash  = CheckCollisionPointRec(mouse, cashBtn);
            int mouseOverBkash = CheckCollisionPointRec(mouse, bkashBtn);
            int mouseOverNagad = CheckCollisionPointRec(mouse, nagadBtn);

            if (downPressed || rightPressed) kbIndex = (kbIndex + 1) % 3;
            if (upPressed || leftPressed) kbIndex = (kbIndex - 1 + 3) % 3;

            DrawTextExBold(customFont, "Select payment method", (Vector2){300, 150}, 43, 1, titleColor);

            DrawMCButton(cashBtn, "Cash", mouseOverCash || kbIndex == 0, 41);
            DrawMCButton(bkashBtn, "bKash", mouseOverBkash || kbIndex == 1, 41);
            DrawMCButton(nagadBtn, "Nagad", mouseOverNagad || kbIndex == 2, 41);

            if ((clicked && mouseOverCash) || (kbIndex == 0 && enterPressed)) {
                strcpy(payName, "Cash");
                screen = 9;
                kbIndex = 0;
            }
            if ((clicked && mouseOverBkash) || (kbIndex == 1 && enterPressed)) {
                strcpy(payName, "bKash");
                screen = 9;
                kbIndex = 0;
            }
            if ((clicked && mouseOverNagad) || (kbIndex == 2 && enterPressed)) {
                strcpy(payName, "Nagad");
                screen = 9;
                kbIndex = 0;
            }

        } else {

            char line1[60];
            char line2[80];
            char line3[60];
            Rectangle okBtn = {400, 480, 220, 75};
            int mouseOverOk = CheckCollisionPointRec(mouse, okBtn);

            DrawTextExBold(customFont, "Yay! Can't wait for the drink! ^_^", (Vector2){170, 200}, 38, 1, titleColor);
            sprintf(line1, "Cup: %s (%d ml)", cupSizes[cupChoice - 1].name, cupMl);
            DrawTextExBold(customFont, line1, (Vector2){260, 265}, 26, 1, textColor);
            sprintf(line2, "Payment via %s confirmed.", payName);
            DrawTextExBold(customFont, line2, (Vector2){260, 300}, 29, 1, textColor);
            sprintf(line3, "Total paid: %d Tk", totalPrice());
            DrawTextExBold(customFont, line3, (Vector2){330, 340}, 29, 1, textColor);

            DrawMCButton(okBtn, "OK", mouseOverOk || kbIndex == 0, 41);
            if ((mouseOverOk && clicked) || enterPressed) {
                EndDrawing();
                return;
            }
        }

        if (fadeAlpha > 0) {
            DrawRectangle(0, 0, 1050, 740, Fade(bg, (float)fadeAlpha / 255.0f));
            fadeAlpha = fadeAlpha - 30;
            if (fadeAlpha < 0) fadeAlpha = 0;
        }

        EndDrawing();
    }

    exit(0);
}
int main(void) {

    int kbIndex = 0;

    initData();

    InitWindow(1050, 740, "Tap Tap Coffee");

    customFont = LoadFont("Baloo2-Regular.ttf");

    SetTargetFPS(60);

    Color bgColor = (Color){255, 240, 245, 255};
    Color titleColor = (Color){150, 90, 100, 255};
    Color textColor = (Color){90, 70, 70, 255};

    Rectangle normalBtn = {330, 280, 400, 90};
    Rectangle customBtn = {330, 395, 400, 90};
    Rectangle exitBtn   = {330, 510, 400, 90};

    while (!WindowShouldClose()) {

        Vector2 mouse = GetMousePosition();

        int mouseOverNormal = CheckCollisionPointRec(mouse, normalBtn);
        int mouseOverCustom = CheckCollisionPointRec(mouse, customBtn);
        int mouseOverExit   = CheckCollisionPointRec(mouse, exitBtn);

        int clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        int enterPressed = IsKeyPressed(KEY_ENTER);

        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_RIGHT)) kbIndex = (kbIndex + 1) % 3;
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_LEFT)) kbIndex = (kbIndex - 1 + 3) % 3;

        BeginDrawing();
        ClearBackground(bgColor);

        {
            const char *line1 = "~*~ TAP TAP COFFEE ~*~";
            const char *line2 = "Your cute drink corner!";
            const char *line3 = "Pick your adventure:";
            Vector2 s1 = MeasureTextEx(customFont, line1, 62, 1);
            Vector2 s2 = MeasureTextEx(customFont, line2, 34, 1);
            Vector2 s3 = MeasureTextEx(customFont, line3, 36, 1);

            DrawTextExBold(customFont, line1, (Vector2){(1050 - s1.x) / 2, 90}, 62, 1, titleColor);
            DrawTextExBold(customFont, line2, (Vector2){(1050 - s2.x) / 2, 90 + s1.y + 6}, 34, 1, textColor);
            DrawTextExBold(customFont, line3, (Vector2){(1050 - s3.x) / 2, 90 + s1.y + 6 + s2.y + 4}, 36, 1, textColor);
        }

        DrawMCButton(normalBtn, "1. Normal Menu", mouseOverNormal || kbIndex == 0, 46);
        DrawMCButton(customBtn, "2. Custom Menu", mouseOverCustom || kbIndex == 1, 46);
        DrawMCButton(exitBtn, "3. Exit", mouseOverExit || kbIndex == 2, 46);

        EndDrawing();

        if ((mouseOverNormal && clicked) || (kbIndex == 0 && enterPressed)) {
            showNormalMenu();
        }

        if ((mouseOverCustom && clicked) || (kbIndex == 1 && enterPressed)) {
            showCustomMenu();
        }

        if ((mouseOverExit && clicked) || (kbIndex == 2 && enterPressed)) {
            break;
        }
    }

    UnloadFont(customFont);
    CloseWindow();

    return 0;
}