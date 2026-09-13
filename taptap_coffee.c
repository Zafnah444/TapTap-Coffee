#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define MAX_INGREDIENTS  50
#define MAX_NORMAL_ITEMS 10

struct Ingredient {
    char name[60];
    int price;
    int ml;
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
};

struct CartEntry {
    int index;
    int isTopping;
    int portions;
};

struct Ingredient baseIngredients[8];
struct Ingredient toppingIngredients[21];
struct CupSize cupSizes[4];
struct NormalItem normalMenu[10];
struct CartEntry cart[MAX_INGREDIENTS];
int cartSize = 0;
Font customFont;

void initData(void) {
    strcpy(baseIngredients[0].name, "Sugarcane (200 ml)");
    baseIngredients[0].price = 50;
    baseIngredients[0].ml = 200;

    strcpy(baseIngredients[1].name, "Lemonade (200 ml)");
    baseIngredients[1].price = 60;
    baseIngredients[1].ml = 200;

    strcpy(baseIngredients[2].name, "Chilled Water (200 ml)");
    baseIngredients[2].price = 0;
    baseIngredients[2].ml = 200;

    strcpy(baseIngredients[3].name, "Regular Milk (200 ml, normal)");
    baseIngredients[3].price = 40;
    baseIngredients[3].ml = 200;

    strcpy(baseIngredients[4].name, "Regular Milk Chilled (200 ml)");
    baseIngredients[4].price = 40;
    baseIngredients[4].ml = 200;

    strcpy(baseIngredients[5].name, "Crushed Ice Milk (200 ml)");
    baseIngredients[5].price = 50;
    baseIngredients[5].ml = 200;

    strcpy(baseIngredients[6].name, "Coconut Water (200 ml)");
    baseIngredients[6].price = 80;
    baseIngredients[6].ml = 200;

    strcpy(baseIngredients[7].name, "Double Shot Espresso (60 ml)");
    baseIngredients[7].price = 200;
    baseIngredients[7].ml = 60;

    strcpy(toppingIngredients[0].name, "Mint");
    toppingIngredients[0].price = 20;
    toppingIngredients[0].ml = 10;

    strcpy(toppingIngredients[1].name, "Instant Coffee (Nescafe Gold)");
    toppingIngredients[1].price = 40;
    toppingIngredients[1].ml = 10;

    strcpy(toppingIngredients[2].name, "Ice");
    toppingIngredients[2].price = 0;
    toppingIngredients[2].ml = 50;

    strcpy(toppingIngredients[3].name, "Basil Seed");
    toppingIngredients[3].price = 10;
    toppingIngredients[3].ml = 20;

    strcpy(toppingIngredients[4].name, "Boba Pearls");
    toppingIngredients[4].price = 60;
    toppingIngredients[4].ml = 50;

    strcpy(toppingIngredients[5].name, "Coconut Jelly");
    toppingIngredients[5].price = 100;
    toppingIngredients[5].ml = 50;

    strcpy(toppingIngredients[6].name, "Coffee Jelly");
    toppingIngredients[6].price = 100;
    toppingIngredients[6].ml = 50;

    strcpy(toppingIngredients[7].name, "Chocolate Syrup");
    toppingIngredients[7].price = 30;
    toppingIngredients[7].ml = 30;

    strcpy(toppingIngredients[8].name, "Strawberry Syrup");
    toppingIngredients[8].price = 30;
    toppingIngredients[8].ml = 30;

    strcpy(toppingIngredients[9].name, "Dark Chocolate (crushed)");
    toppingIngredients[9].price = 80;
    toppingIngredients[9].ml = 30;

    strcpy(toppingIngredients[10].name, "Strawberry Jam");
    toppingIngredients[10].price = 20;
    toppingIngredients[10].ml = 20;

    strcpy(toppingIngredients[11].name, "Crushed Ice Strawberry");
    toppingIngredients[11].price = 50;
    toppingIngredients[11].ml = 60;

    strcpy(toppingIngredients[12].name, "Blended Pineapple");
    toppingIngredients[12].price = 20;
    toppingIngredients[12].ml = 80;

    strcpy(toppingIngredients[13].name, "Apple Juice");
    toppingIngredients[13].price = 30;
    toppingIngredients[13].ml = 80;

    strcpy(toppingIngredients[14].name, "Blended Mango");
    toppingIngredients[14].price = 20;
    toppingIngredients[14].ml = 80;

    strcpy(toppingIngredients[15].name, "Blended Blueberry");
    toppingIngredients[15].price = 80;
    toppingIngredients[15].ml = 80;

    strcpy(toppingIngredients[16].name, "Blended Banana");
    toppingIngredients[16].price = 20;
    toppingIngredients[16].ml = 80;

    strcpy(toppingIngredients[17].name, "Chopped Banana");
    toppingIngredients[17].price = 20;
    toppingIngredients[17].ml = 40;

    strcpy(toppingIngredients[18].name, "Chopped Mango");
    toppingIngredients[18].price = 20;
    toppingIngredients[18].ml = 40;

    strcpy(toppingIngredients[19].name, "Chopped Apple");
    toppingIngredients[19].price = 30;
    toppingIngredients[19].ml = 40;

    strcpy(toppingIngredients[20].name, "Papaya Juice");
    toppingIngredients[20].price = 20;
    toppingIngredients[20].ml = 80;

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
}

void pauseAnyKey(void) {
    printf("\n  Press Enter to continue...");
    int c;
    while ((c = getchar()) != '\n');
    getchar();
}

int hasMilk(void) {
    int i;
    for (i = 0; i < cartSize; i++) {
        if (cart[i].isTopping == 0) {
            if (strstr(baseIngredients[cart[i].index].name, "ilk") != NULL) {
                return 1;
            }
        }
    }
    return 0;
}

int hasEspresso(void) {
    int i;
    for (i = 0; i < cartSize; i++) {
        if (cart[i].isTopping == 0) {
            if (strstr(baseIngredients[cart[i].index].name, "spresso") != NULL) {
                return 1;
            }
        }
    }
    return 0;
}

int hasInstantCoffee(void) {
    int i;
    for (i = 0; i < cartSize; i++) {
        if (cart[i].isTopping == 1) {
            if (strstr(toppingIngredients[cart[i].index].name, "Instant") != NULL) {
                return 1;
            }
        }
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

void DrawMCButton(Rectangle r, const char *label, int hovered, int fontSize) {
    Color colorA = hovered ? mcHoverA : mcBaseA;
    Color colorB = hovered ? mcHoverB : mcBaseB;
    Color txt = hovered ? mcTextHover : mcTextNormal;
    Vector2 sz = MeasureTextEx(customFont, label, (float)fontSize, 1);
    float tx = r.x + (r.width - sz.x) / 2;
    float ty = r.y + (r.height - sz.y) / 2;

    DrawPixelFill(r, colorA, colorB, 6);
    DrawLine((int)r.x, (int)r.y, (int)(r.x + r.width), (int)r.y, mcHighlight);
    DrawLine((int)r.x, (int)r.y, (int)r.x, (int)(r.y + r.height), mcHighlight);
    DrawLine((int)(r.x + r.width), (int)r.y, (int)(r.x + r.width), (int)(r.y + r.height), mcShadowLine);
    DrawLine((int)r.x, (int)(r.y + r.height), (int)(r.x + r.width), (int)(r.y + r.height), mcShadowLine);
    DrawRectangleLinesEx(r, 3, mcBorderDark);

    DrawTextEx(customFont, label, (Vector2){tx + 2, ty + 2}, (float)fontSize, 1, mcTextShadow);
    DrawTextEx(customFont, label, (Vector2){tx, ty}, (float)fontSize, 1, txt);
}

void DrawMCButtonDisabled(Rectangle r, const char *label, int fontSize) {
    Vector2 sz = MeasureTextEx(customFont, label, (float)fontSize, 1);
    float tx = r.x + (r.width - sz.x) / 2;
    float ty = r.y + (r.height - sz.y) / 2;

    DrawPixelFill(r, mcDisabledA, mcDisabledB, 6);
    DrawRectangleLinesEx(r, 3, mcBorderDark);
    DrawTextEx(customFont, label, (Vector2){tx, ty}, (float)fontSize, 1, mcTextDisabled);
}

void DrawCupVisual(int cx, int topY, int height, float fillFraction) {
    int topWidth = 220;
    int bottomWidth = 150;
    int sliceH = 6;
    int numSlices = height / sliceH;
    int i;
    Color cupColorA = (Color){235, 242, 252, 255};
    Color cupColorB = (Color){222, 232, 248, 255};
    Color liquidColorA = (Color){225, 190, 160, 255};
    Color liquidColorB = (Color){210, 175, 145, 255};
    Color outline = mcBorderDark;
    float liquidTopFrac;

    if (fillFraction < 0) fillFraction = 0;
    if (fillFraction > 1) fillFraction = 1;
    liquidTopFrac = 1.0f - fillFraction;

    for (i = 0; i < numSlices; i++) {
        float frac = (float)i / (numSlices - 1);
        int w = (int)(topWidth + (bottomWidth - topWidth) * frac);
        int y = topY + i * sliceH;
        int isLiquid = frac >= liquidTopFrac;
        Color a = isLiquid ? liquidColorA : cupColorA;
        Color b = isLiquid ? liquidColorB : cupColorB;
        Color c = ((i / 2) % 2 == 0) ? a : b;
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

int chooseIngredient(struct Ingredient *list, int count, int isTopping, int budget, int cupMl, int skipMilkWarning) {
    int choice;
    int portions;
    int i;
    int remaining;
    int remainingBudget;
    int ok;
    char marker[2];
    int wc;
    int merged;

    remaining = cupMl - totalMl();
    remainingBudget = budget - totalPrice();

    printf("\n  Cup space: %d ml | Budget: %d Tk\n", remaining, remainingBudget);
    printf("  Enter number (0 = back):\n\n");

    for (i = 0; i < count; i++) {
        if (list[i].price <= remainingBudget && list[i].ml <= remaining) {
            ok = 1;
            strcpy(marker, "+");
        } else {
            ok = 0;
            strcpy(marker, "-");
        }
        printf("  %s %2d. %-34s %3d Tk  %d ml\n",
               marker, i + 1, list[i].name, list[i].price, list[i].ml);
    }

    printf("\n  - = can't afford or won't fit\n  Choice: ");
    scanf("%d", &choice);

    if (choice == 0) {
        return 0;
    }

    if (choice < 1 || choice > count) {
        printf("  Invalid!\n");
        pauseAnyKey();
        return 0;
    }

    choice = choice - 1;

    if (list[choice].price > remainingBudget) {
        printf("  Not enough budget!\n");
        pauseAnyKey();
        return 0;
    }

    if (list[choice].ml > remaining) {
        printf("  Not enough cup space!\n");
        pauseAnyKey();
        return 0;
    }

    printf("  How many portions? ");
    scanf("%d", &portions);

    if (portions < 1) {
        printf("  Invalid.\n");
        pauseAnyKey();
        return 0;
    }

    if (list[choice].ml * portions > remaining) {
        printf("  Too many for the cup!\n");
        pauseAnyKey();
        return 0;
    }

    if (list[choice].price * portions > remainingBudget) {
        printf("  Too expensive!\n");
        pauseAnyKey();
        return 0;
    }

    if (skipMilkWarning == 0 && hasMilk() == 1) {
        if (strstr(list[choice].name, "ineapple") != NULL) {
            printf("  Are you sure? This may create stomach problems!\n");
            printf("    1. Cancel\n    2. Proceed anyway\n  Choice: ");
            scanf("%d", &wc);
            if (wc != 2) {
                printf("  Cancelled.\n");
                pauseAnyKey();
                return 0;
            }
        }
    }

    if (hasEspresso() == 1 && hasInstantCoffee() == 0) {
        if (strstr(list[choice].name, "Instant") != NULL) {
            printf("  Wow, can you handle the bitterness?\n");
            printf("    1. Yes, I can!\n    2. No, cancel\n  Choice: ");
            scanf("%d", &wc);
            if (wc != 1) {
                printf("  Cancelled.\n");
                pauseAnyKey();
                return 0;
            }
        }
    }

    if (hasInstantCoffee() == 1 && hasEspresso() == 0) {
        if (strstr(list[choice].name, "spresso") != NULL) {
            printf("  Wow, can you handle the bitterness?\n");
            printf("    1. Yes, I can!\n    2. No, cancel\n  Choice: ");
            scanf("%d", &wc);
            if (wc != 1) {
                printf("  Cancelled.\n");
                pauseAnyKey();
                return 0;
            }
        }
    }

    merged = 0;
    for (i = 0; i < cartSize; i++) {
        if (cart[i].isTopping == isTopping && cart[i].index == choice) {
            cart[i].portions = cart[i].portions + portions;
            printf("  Added %d more of %s\n", portions, list[choice].name);
            pauseAnyKey();
            return 1;
        }
    }

    if (cartSize >= MAX_INGREDIENTS) {
        printf("  Cart full!\n");
        pauseAnyKey();
        return 0;
    }

    cart[cartSize].index = choice;
    cart[cartSize].isTopping = isTopping;
    cart[cartSize].portions = portions;
    cartSize = cartSize + 1;

    printf("  Added %d portion(s) of %s\n", portions, list[choice].name);
    pauseAnyKey();
    return 1;
}

void showNormalMenu(void) {
    struct NormalCartEntry cartNormal[MAX_NORMAL_ITEMS];
    int cartNCount = 0;
    int i, j, id, sub, total;
    int screen = 0;
    int kbIndex = 0;
    int kbCol = 0;
    int kbRow = 0;
    int lastScreen = -1;
    int fadeAlpha = 0;
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

            int leftLen = 10;
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

            DrawTextEx(customFont, "Normal Menu - pick a drink", (Vector2){20, 15}, 41, 1, titleColor);

            for (i = 0; i < 10; i++) {
                Rectangle row = {20, 65 + i * 48, 620, 44};
                char label[100];

                mouseOverRow = CheckCollisionPointRec(mouse, row);
                hoveredRow = mouseOverRow || (kbCol == 0 && kbRow == i);

                sprintf(label, "%-28s %d Tk", normalMenu[i].name, normalMenu[i].price);
                DrawMCButton(row, label, hoveredRow, 29);

                if ((mouseOverRow && clicked) || (kbCol == 0 && kbRow == i && enterPressed)) {
                    int found = 0;
                    for (j = 0; j < cartNCount; j++) {
                        if (cartNormal[j].id == i) {
                            cartNormal[j].qty = cartNormal[j].qty + 1;
                            found = 1;
                            break;
                        }
                    }
                    if (!found && cartNCount < MAX_NORMAL_ITEMS) {
                        cartNormal[cartNCount].id = i;
                        cartNormal[cartNCount].qty = 1;
                        cartNCount = cartNCount + 1;
                    }
                }
            }

            DrawTextEx(customFont, "Your Cart:", (Vector2){680, 15}, 36, 1, titleColor);
            total = 0;

            for (i = 0; i < cartNCount; i++) {
                char line[100];
                Rectangle minusBtn = {920, 58 + i * 36, 46, 32};
                int mouseOverMinus = CheckCollisionPointRec(mouse, minusBtn);
                int hoveredMinus = mouseOverMinus || (kbCol == 1 && kbRow == i);

                id = cartNormal[i].id;
                sub = normalMenu[id].price * cartNormal[i].qty;
                total = total + sub;

                sprintf(line, "%dx %s = %d Tk", cartNormal[i].qty, normalMenu[id].name, sub);
                DrawTextEx(customFont, line, (Vector2){680, 60 + i * 36}, 22, 1, textColor);

                DrawMCButton(minusBtn, "-", hoveredMinus, 26);

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
                DrawTextEx(customFont, totalLine, (Vector2){680, 500}, 34, 1, titleColor);

                DrawMCButton(checkoutBtn, "Checkout", hoveredCheckout, 31);
                DrawMCButton(backBtn, "Back to Main Menu", hoveredBack, 24);

                if (((mouseOverCheckout && clicked) || (kbCol == 1 && kbRow == checkoutRow && enterPressed)) && cartNCount > 0) {
                    screen = 1;
                    kbIndex = 0;
                }
                if ((mouseOverBack && clicked) || (kbCol == 1 && kbRow == backRow && enterPressed)) {
                    EndDrawing();
                    return;
                }
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

            DrawTextEx(customFont, "Select payment method", (Vector2){300, 150}, 43, 1, titleColor);

            DrawMCButton(cashBtn, "Cash", mouseOverCash || kbIndex == 0, 34);
            DrawMCButton(bkashBtn, "bKash", mouseOverBkash || kbIndex == 1, 34);
            DrawMCButton(nagadBtn, "Nagad", mouseOverNagad || kbIndex == 2, 34);

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
                total = total + normalMenu[id].price * cartNormal[i].qty;
            }

            DrawTextEx(customFont, "Yay! Can't wait for the drink! ^_^", (Vector2){190, 210}, 38, 1, titleColor);

            sprintf(line2, "Payment via %s confirmed.", payName);
            DrawTextEx(customFont, line2, (Vector2){260, 280}, 31, 1, textColor);

            sprintf(line3, "Total paid: %d Tk", total);
            DrawTextEx(customFont, line3, (Vector2){330, 325}, 31, 1, textColor);

            DrawMCButton(okBtn, "OK", mouseOverOk || kbIndex == 0, 34);

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
    int pendingIsTopping;
    int pendingIndex;
    int pendingPortions;
    int warningType;
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

            if (downPressed) gridRow = (gridRow + 1) % gridRows;
            if (upPressed) gridRow = (gridRow - 1 + gridRows) % gridRows;
            if (rightPressed) gridCol = (gridCol + 1) % gridCols;
            if (leftPressed) gridCol = (gridCol - 1 + gridCols) % gridCols;
            kbIndex = gridRow * gridCols + gridCol;
            if (kbIndex >= slots) kbIndex = slots - 1;

            if (isPortions) {
                char hd[100];
                sprintf(hd, "How many portions of %s?", pendingList[pendingIndex].name);
                DrawTextEx(customFont, hd, (Vector2){20, 20}, 36, 1, titleColor);
            } else {
                DrawTextEx(customFont, "Hi! What's your budget?", (Vector2){20, 20}, 41, 1, titleColor);
            }

            DrawTextEx(customFont, numBuffer[0] ? numBuffer : "0", (Vector2){40, 90}, 67, 1, textColor);
            if (!isPortions) {
                DrawTextEx(customFont, "Tk", (Vector2){340, 105}, 38, 1, textColor);
            }

            for (i = 0; i < 9; i++) {
                Rectangle r = {40 + (i % 3) * 130, 180 + (i / 3) * 95, 115, 82};
                int mouseOver = CheckCollisionPointRec(mouse, r);
                int hovered = mouseOver || (kbIndex == i);
                char label[2] = { (char)('1' + i), '\0' };
                DrawMCButton(r, label, hovered, 38);
                if ((mouseOver && clicked && strlen(numBuffer) < maxDigits) ||
                    (kbIndex == i && enterPressed && strlen(numBuffer) < maxDigits)) {
                    strcat(numBuffer, label);
                }
            }

            {
                Rectangle zeroR = {40, 465, 115, 82};
                Rectangle delR = {170, 465, 115, 82};
                Rectangle okR = {300, 465, 195, 82};
                int mouseOverZero = CheckCollisionPointRec(mouse, zeroR);
                int mouseOverDel = CheckCollisionPointRec(mouse, delR);
                int mouseOverOk = CheckCollisionPointRec(mouse, okR);

                DrawMCButton(zeroR, "0", mouseOverZero || kbIndex == 9, 38);
                DrawMCButton(delR, "Del", mouseOverDel || kbIndex == 10, 31);
                DrawMCButton(okR, "Confirm", mouseOverOk || kbIndex == 11, 31);

                if (((mouseOverZero && clicked) || (kbIndex == 9 && enterPressed)) && strlen(numBuffer) < maxDigits) {
                    strcat(numBuffer, "0");
                }
                if (((mouseOverDel && clicked) || (kbIndex == 10 && enterPressed)) && strlen(numBuffer) > 0) {
                    numBuffer[strlen(numBuffer) - 1] = '\0';
                }

                if (isPortions) {
                    Rectangle cancelR = {300, 560, 195, 65};
                    int mouseOverCancel = CheckCollisionPointRec(mouse, cancelR);
                    DrawMCButton(cancelR, "Cancel", mouseOverCancel, 29);
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
                            warningType = 0;
                            if (pendingIsTopping) {
                                if (hasMilk() && strstr(ch->name, "ineapple") != NULL) {
                                    warningType = 1;
                                } else if (hasEspresso() && strstr(ch->name, "Instant") != NULL) {
                                    warningType = 2;
                                } else if (hasInstantCoffee() && strstr(ch->name, "spresso") != NULL) {
                                    warningType = 3;
                                }
                            } else {
                                if (hasMilk() && strstr(ch->name, "ineapple") != NULL) {
                                    warningType = 1;
                                } else if (hasEspresso() && !hasInstantCoffee() && strstr(ch->name, "Instant") != NULL) {
                                    warningType = 2;
                                } else if (hasInstantCoffee() && !hasEspresso() && strstr(ch->name, "spresso") != NULL) {
                                    warningType = 3;
                                }
                            }

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
            DrawTextEx(customFont, line, (Vector2){40, 30}, 41, 1, titleColor);

            for (i = 0; i < 4; i++) {
                Rectangle r = {40, 100 + i * 95, 480, 80};
                int mouseOver = CheckCollisionPointRec(mouse, r);
                int hovered = mouseOver || (kbIndex == i);
                char lbl[60];
                sprintf(lbl, "%s (%d ml)", cupSizes[i].name, cupSizes[i].ml);
                DrawMCButton(r, lbl, hovered, 34);
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
            float fillFrac = (cupMl > 0) ? ((float)totalMl() / (float)cupMl) : 0;

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
                DrawTextEx(customFont, line1, (Vector2){(1050 - s1.x) / 2, 15}, 27, 1, titleColor);
                DrawTextEx(customFont, line2, (Vector2){(1050 - s2.x) / 2, 48}, 27, 1, titleColor);

                {
                    const char *cupLabel = "Your cup so far:";
                    Vector2 s3 = MeasureTextEx(customFont, cupLabel, 30, 1);
                    DrawTextEx(customFont, cupLabel, (Vector2){(1050 - s3.x) / 2, 85}, 30, 1, titleColor);
                }

                DrawCupVisual(350, 220, 240, fillFrac);

                DrawTextEx(customFont, "In your cup:", (Vector2){650, 130}, 26, 1, titleColor);
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
                    DrawTextEx(customFont, nline, (Vector2){650, 165 + i * 26}, 18, 1, textColor);
                }

                DrawMCButton(addBaseBtn, "Add Base", hoveredAddBase, 26);
                DrawMCButton(addTopBtn, "Add Toppings", hoveredAddTop, 26);
                DrawMCButton(undoBtn, "Undo Last", hoveredUndo, 26);
                DrawMCButton(doneBtn, "Checkout", hoveredDone, 26);
                DrawMCButton(cancelBtn, "Cancel", hoveredCancel, 26);

                if ((mouseOverAddBase && clicked) || (kbRow == 0 && kbCol == 0 && enterPressed)) {
                    pendingList = baseIngredients;
                    pendingIsTopping = 0;
                    screen = 3;
                    kbIndex = 0;
                    kbCol = 0;
                    kbRow = 0;
                }
                if ((mouseOverAddTop && clicked) || (kbRow == 0 && kbCol == 1 && enterPressed)) {
                    pendingList = toppingIngredients;
                    pendingIsTopping = 1;
                    toppingPage = 0;
                    screen = 4;
                    kbIndex = 0;
                    kbCol = 0;
                    kbRow = 0;
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

        } else if (screen == 3 || screen == 4) {

            int listStart;
            int listEnd;
            int isTop = (screen == 4);
            struct Ingredient *list = isTop ? toppingIngredients : baseIngredients;
            int remaining = cupMl - totalMl();
            int remainingBudget = budget - totalPrice();
            int rowCount;
            int sideLen;
            char hd[80];

            if (isTop) {
                if (toppingPage == 0) {
                    listStart = 0;
                    listEnd = 11;
                } else {
                    listStart = 11;
                    listEnd = 21;
                }
            } else {
                listStart = 0;
                listEnd = 8;
            }

            rowCount = listEnd - listStart;
            sideLen = (isTop ? 2 : 0) + 1;

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

            sprintf(hd, "%s - Space:%dml Budget:%dTk", isTop ? "Toppings" : "Base Ingredients", remaining, remainingBudget);
            DrawTextEx(customFont, hd, (Vector2){20, 15}, 31, 1, titleColor);

            for (i = listStart; i < listEnd; i++) {
                Rectangle r = {20, 60 + (i - listStart) * 46, 700, 40};
                int mouseOver = CheckCollisionPointRec(mouse, r);
                int slotIdx = i - listStart;
                int hovered = mouseOver || (kbCol == 0 && kbRow == slotIdx);
                int afford = (list[i].price <= remainingBudget && list[i].ml <= remaining);
                char lbl[100];
                sprintf(lbl, "%s  %d Tk  %d ml", list[i].name, list[i].price, list[i].ml);

                if (afford) {
                    DrawMCButton(r, lbl, hovered, 24);
                } else {
                    DrawMCButtonDisabled(r, lbl, 24);
                }

                if (afford && ((mouseOver && clicked) || (kbCol == 0 && kbRow == slotIdx && enterPressed))) {
                    pendingList = list;
                    pendingIsTopping = isTop;
                    pendingIndex = i;
                    numBuffer[0] = '\0';
                    screen = 5;
                    kbIndex = 0;
                }
            }

            if (isTop) {
                Rectangle prevBtn = {740, 60, 130, 50};
                Rectangle nextBtn = {740, 120, 130, 50};
                int mouseOverPrev = CheckCollisionPointRec(mouse, prevBtn);
                int mouseOverNext = CheckCollisionPointRec(mouse, nextBtn);

                DrawMCButton(prevBtn, "Prev", mouseOverPrev || (kbCol == 1 && kbRow == 0), 24);
                DrawMCButton(nextBtn, "Next", mouseOverNext || (kbCol == 1 && kbRow == 1), 24);

                if ((mouseOverPrev && clicked) || (kbCol == 1 && kbRow == 0 && enterPressed)) {
                    toppingPage = 0;
                    kbRow = 0;
                }
                if ((mouseOverNext && clicked) || (kbCol == 1 && kbRow == 1 && enterPressed)) {
                    toppingPage = 1;
                    kbRow = 0;
                }
            }

            {
                Rectangle backBtn = {740, 590, 170, 60};
                int mouseOverBack = CheckCollisionPointRec(mouse, backBtn);
                int backRow = sideLen - 1;
                DrawMCButton(backBtn, "Back", mouseOverBack || (kbCol == 1 && kbRow == backRow), 26);
                if ((mouseOverBack && clicked) || (kbCol == 1 && kbRow == backRow && enterPressed)) {
                    screen = 2;
                    kbIndex = 0;
                    kbCol = 0;
                    kbRow = 0;
                }
            }

        } else if (screen == 6) {

            char msg[100];
            Rectangle yesBtn = {230, 320, 240, 75};
            Rectangle noBtn  = {530, 320, 240, 75};
            int mouseOverYes = CheckCollisionPointRec(mouse, yesBtn);
            int mouseOverNo = CheckCollisionPointRec(mouse, noBtn);

            if (rightPressed) kbIndex = (kbIndex + 1) % 2;
            if (leftPressed) kbIndex = (kbIndex - 1 + 2) % 2;

            if (warningType == 1) {
                strcpy(msg, "Are you sure? This may create stomach problems!");
            } else {
                strcpy(msg, "Wow, can you handle the bitterness?");
            }
            {
                Vector2 msgSize = MeasureTextEx(customFont, msg, 40, 1);
                DrawTextEx(customFont, msg, (Vector2){(1050 - msgSize.x) / 2, 200}, 40, 1, titleColor);
            }

            DrawMCButton(yesBtn, warningType == 1 ? "Proceed anyway" : "Yes, I can!", mouseOverYes || kbIndex == 0, 26);
            DrawMCButton(noBtn, warningType == 1 ? "Cancel" : "No, cancel", mouseOverNo || kbIndex == 1, 26);

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
                DrawTextEx(customFont, msg, (Vector2){(1050 - msgSize.x) / 2, 250}, 40, 1, titleColor);
            }

            DrawMCButton(yesBtn, "Yes, go back", mouseOverYes || kbIndex == 0, 26);
            DrawMCButton(noBtn, "No, stay", mouseOverNo || kbIndex == 1, 26);

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

            DrawTextEx(customFont, "Select payment method", (Vector2){300, 150}, 43, 1, titleColor);

            DrawMCButton(cashBtn, "Cash", mouseOverCash || kbIndex == 0, 34);
            DrawMCButton(bkashBtn, "bKash", mouseOverBkash || kbIndex == 1, 34);
            DrawMCButton(nagadBtn, "Nagad", mouseOverNagad || kbIndex == 2, 34);

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

            DrawTextEx(customFont, "Yay! Can't wait for the drink! ^_^", (Vector2){170, 200}, 38, 1, titleColor);
            sprintf(line1, "Cup: %s (%d ml)", cupSizes[cupChoice - 1].name, cupMl);
            DrawTextEx(customFont, line1, (Vector2){260, 265}, 26, 1, textColor);
            sprintf(line2, "Payment via %s confirmed.", payName);
            DrawTextEx(customFont, line2, (Vector2){260, 300}, 29, 1, textColor);
            sprintf(line3, "Total paid: %d Tk", totalPrice());
            DrawTextEx(customFont, line3, (Vector2){330, 340}, 29, 1, textColor);

            DrawMCButton(okBtn, "OK", mouseOverOk || kbIndex == 0, 34);
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

            DrawTextEx(customFont, line1, (Vector2){(1050 - s1.x) / 2, 90}, 62, 1, titleColor);
            DrawTextEx(customFont, line2, (Vector2){(1050 - s2.x) / 2, 90 + s1.y + 6}, 34, 1, textColor);
            DrawTextEx(customFont, line3, (Vector2){(1050 - s3.x) / 2, 90 + s1.y + 6 + s2.y + 4}, 36, 1, textColor);
        }

        DrawMCButton(normalBtn, "1. Normal Menu", mouseOverNormal || kbIndex == 0, 38);
        DrawMCButton(customBtn, "2. Custom Menu", mouseOverCustom || kbIndex == 1, 38);
        DrawMCButton(exitBtn, "3. Exit", mouseOverExit || kbIndex == 2, 38);

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