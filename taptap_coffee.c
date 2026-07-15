#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    /* milk + pineapple warning */
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

    /* espresso + instant coffee warning */
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

    /* instant coffee + espresso warning */
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

    /* check if already in cart, merge */
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
    int total = 0;
    int choice;
    int i;
    int j;
    int found;
    int id;
    int sub;
    int qty;
    int rmIdx;
    int pay;
    char payName[10];

    while (1) {

        printf("\n  ===== NORMAL MENU =====\n\n");

        for (i = 0; i < 10; i++) {
            printf("  %2d. %-28s %d Tk\n      %s\n\n", i + 1, normalMenu[i].name, normalMenu[i].price, normalMenu[i].desc);
        }

        if (cartNCount > 0) {
            printf("\n  Your Cart:\n");
            total = 0;
            for (i = 0; i < cartNCount; i++) {
                id = cartNormal[i].id;
                sub = normalMenu[id].price * cartNormal[i].qty;
                printf("    %d x %-28s %d Tk\n", cartNormal[i].qty, normalMenu[id].name, sub);
                total = total + sub;
            }
            printf("  Total: %d Tk\n", total);
        }

        printf("\n  Enter drink number to add\n");
        printf("  0 = confirm & pay | -1 = remove item | -2 = back\n\n  Choice: ");
        scanf("%d", &choice);

        if (choice == -2) {
            return;
        }

        if (choice == 0) {
            if (cartNCount == 0) {
                printf("\n  Cart is empty!\n");
                pauseAnyKey();
                continue;
            }

    
            printf("\n  ===== ORDER SUMMARY =====\n\n");
            total = 0;

            for (i = 0; i < cartNCount; i++) {
                id = cartNormal[i].id;
                sub = normalMenu[id].price * cartNormal[i].qty;
                printf("  %d x %-28s %d Tk\n", cartNormal[i].qty, normalMenu[id].name, sub);
                total = total + sub;
            }

            printf("  TOTAL: %d Tk\n", total);

            printf("\n  Select payment method:\n");
            printf("    1. Cash\n    2. bKash\n    3. Nagad\n\n  Choice: ");
            scanf("%d", &pay);

            if (pay < 1 || pay > 3) {
                pay = 1;
            }

            if (pay == 1) {
                strcpy(payName, "Cash");
            } else if (pay == 2) {
                strcpy(payName, "bKash");
            } else {
                strcpy(payName, "Nagad");
            }

    
            printf("\n  Yay! Can't wait for the drink! ^_^\n\n");
            printf("  Payment via %s confirmed.\n", payName);
            printf("  Total paid: %d Tk\n\n", total);
            pauseAnyKey();
            return;
        }

        if (choice == -1) {
            if (cartNCount == 0) {
                printf("\n  Cart is empty~\n");
                pauseAnyKey();
                continue;
            }

            printf("\n  Enter line to remove (1-%d): ", cartNCount);
            scanf("%d", &rmIdx);

            if (rmIdx < 1 || rmIdx > cartNCount) {
                printf("  Invalid!\n");
                pauseAnyKey();
                continue;
            }

            rmIdx = rmIdx - 1;

            for (j = rmIdx; j < cartNCount - 1; j++) {
                cartNormal[j] = cartNormal[j + 1];
            }

            cartNCount = cartNCount - 1;
            printf("  Removed!\n");
            pauseAnyKey();
            continue;
        }

        if (choice < 1 || choice > 10) {
            printf("  Invalid choice!\n");
            pauseAnyKey();
            continue;
        }

        choice = choice - 1;

        printf("  How many? ");
        scanf("%d", &qty);

        if (qty < 1) {
            printf("  Invalid.\n");
            pauseAnyKey();
            continue;
        }

        found = 0;

        for (i = 0; i < cartNCount; i++) {
            if (cartNormal[i].id == choice) {
                cartNormal[i].qty = cartNormal[i].qty + qty;
                found = 1;
                break;
            }
        }

        if (found == 0 && cartNCount < MAX_NORMAL_ITEMS) {
            cartNormal[cartNCount].id = choice;
            cartNormal[cartNCount].qty = qty;
            cartNCount = cartNCount + 1;
        }

        printf("  Added %d x %s\n", qty, normalMenu[choice].name);
        pauseAnyKey();
    }
}

void showCustomMenu(void) {
    int budget;
    int cupChoice;
    int cupMl;
    int i;
    int running;
    int action;
    int sub;
    int page;
    int half;
    int start;
    int end;
    int tc;
    int tidx;
    int portions;
    int merged;
    int cc;
    int pay;
    int ok;
    char marker[2];
    char payName[10];
    struct Ingredient *ch;

    cartSize = 0;
    cupMl = 0;


    printf("\n  Hi, let's create a drink! It will be so fun!\n\n");
    pauseAnyKey();


    printf("\n  What's your budget today?\n\n  Enter amount in Tk: ");
    scanf("%d", &budget);


    printf("\n  Great! With %d Tk, here are your cup options:\n\n", budget);

    for (i = 0; i < 4; i++) {
        printf("    %d. %-12s (%d ml)\n", i + 1, cupSizes[i].name, cupSizes[i].ml);
    }

    printf("\n  Your choice: ");
    scanf("%d", &cupChoice);

    if (cupChoice < 1 || cupChoice > 4) {
        printf("  Invalid! Defaulting to Pixie.\n");
        cupChoice = 2;
    }

    cupMl = cupSizes[cupChoice - 1].ml;
    printf("\n  You selected: %s (%d ml)\n", cupSizes[cupChoice - 1].name, cupMl);
    pauseAnyKey();


    printf("\n  Let's start filling your %s!\n\n", cupSizes[cupChoice - 1].name);
    printf("  Cup: %d ml | Filled: %d ml\n", cupMl, totalMl());
    pauseAnyKey();

    running = 1;

    while (running == 1) {

        printf("\n  ===== CUSTOMIZE YOUR %s =====\n\n", cupSizes[cupChoice - 1].name);
        printf("  Cup: %d ml | Filled: %d ml\n", cupMl, totalMl());
        printf("  Budget remaining: %d Tk | Cup space: %d ml\n", budget - totalPrice(), cupMl - totalMl());
        printf("  -----------------------------------------\n");
        printf("  Your ingredients:\n");
        showCart();
        printf("  -----------------------------------------\n");

        printf("\n  What would you like to do?\n");
        printf("    1. Add base ingredient\n");
        printf("    2. Add topping\n");
        printf("    3. Undo last ingredient\n");
        printf("    4. Done - proceed to checkout\n");
        printf("    5. Cancel and go back\n\n  Choice: ");
        scanf("%d", &action);

        if (action == 1) {
            sub = 1;
            while (sub == 1) {
        
                printf("\n  ===== BASE INGREDIENTS =====\n\n");
                printf("  Budget: %d Tk | Cup space: %d ml\n", budget - totalPrice(), cupMl - totalMl());
                printf("  -----------------------------------------\n");
                showCart();
                printf("  -----------------------------------------\n");

                if (chooseIngredient(baseIngredients, 8, 0, budget, cupMl, 0) == 0) {
                    sub = 0;
                }
            }
        }

        if (action == 2) {
            page = 1;
            sub = 1;

            while (sub == 1) {
                half = (21 + 1) / 2;

                if (page == 1) {
                    start = 0;
                    end = half;
                } else {
                    start = half;
                    end = 21;
                }

        
                printf("\n  ===== TOPPINGS - Page %d =====\n\n", page);
                printf("  Cup space: %d ml | Budget: %d Tk\n", cupMl - totalMl(), budget - totalPrice());
                printf("  -----------------------------------------\n");
                showCart();
                printf("  -----------------------------------------\n");
                printf("  0=back  -1=prev page  -2=next page\n\n");

                for (i = start; i < end; i++) {
                    if (toppingIngredients[i].price <= budget - totalPrice() &&
                        toppingIngredients[i].ml <= cupMl - totalMl()) {
                        strcpy(marker, "+");
                    } else {
                        strcpy(marker, "-");
                    }
                    printf("  %s %2d. %-34s %3d Tk  %d ml\n",
                           marker, i + 1, toppingIngredients[i].name,
                           toppingIngredients[i].price, toppingIngredients[i].ml);
                }

                printf("\n  Choice: ");
                scanf("%d", &tc);

                if (tc == 0) {
                    sub = 0;
                    break;
                }

                if (tc == -1) {
                    page = 1;
                    continue;
                }

                if (tc == -2) {
                    page = 2;
                    continue;
                }

                if (tc < 1 || tc > 21) {
                    printf("  Invalid!\n");
                    pauseAnyKey();
                    continue;
                }

                tidx = tc - 1;
                ch = &toppingIngredients[tidx];

                if (ch->price > budget - totalPrice()) {
                    printf("  Not enough budget!\n");
                    pauseAnyKey();
                    continue;
                }

                if (ch->ml > cupMl - totalMl()) {
                    printf("  Not enough cup space!\n");
                    pauseAnyKey();
                    continue;
                }

                printf("  How many portions? ");
                scanf("%d", &portions);

                if (portions < 1) {
                    printf("  Invalid.\n");
                    pauseAnyKey();
                    continue;
                }

                if (ch->ml * portions > cupMl - totalMl()) {
                    printf("  Too many for the cup!\n");
                    pauseAnyKey();
                    continue;
                }

                if (ch->price * portions > budget - totalPrice()) {
                    printf("  Too expensive!\n");
                    pauseAnyKey();
                    continue;
                }

                /* milk + pineapple warning */
                if (hasMilk() == 1) {
                    if (strstr(ch->name, "ineapple") != NULL) {
                        printf("  Are you sure? This may create stomach problems!\n");
                        printf("    1. Cancel\n    2. Proceed anyway\n  Choice: ");
                        scanf("%d", &cc);
                        if (cc != 2) {
                            pauseAnyKey();
                            continue;
                        }
                    }
                }

                /* espresso + instant coffee warning */
                if (hasEspresso() == 1) {
                    if (strstr(ch->name, "Instant") != NULL) {
                        printf("  Wow, can you handle the bitterness?\n");
                        printf("    1. Yes, I can!\n    2. No, cancel\n  Choice: ");
                        scanf("%d", &cc);
                        if (cc != 1) {
                            pauseAnyKey();
                            continue;
                        }
                    }
                }

                /* instant coffee + espresso warning */
                if (hasInstantCoffee() == 1) {
                    if (strstr(ch->name, "spresso") != NULL) {
                        printf("  Wow, can you handle the bitterness?\n");
                        printf("    1. Yes, I can!\n    2. No, cancel\n  Choice: ");
                        scanf("%d", &cc);
                        if (cc != 1) {
                            pauseAnyKey();
                            continue;
                        }
                    }
                }

                /* add to cart */
                merged = 0;

                for (i = 0; i < cartSize; i++) {
                    if (cart[i].isTopping == 1 && cart[i].index == tidx) {
                        cart[i].portions = cart[i].portions + portions;
                        merged = 1;
                        break;
                    }
                }

                if (merged == 0 && cartSize < MAX_INGREDIENTS) {
                    cart[cartSize].index = tidx;
                    cart[cartSize].isTopping = 1;
                    cart[cartSize].portions = portions;
                    cartSize = cartSize + 1;
                }

                printf("  Added %d x %s\n", portions, ch->name);
                pauseAnyKey();
            }
        }

        if (action == 3) {
            if (cartSize > 0) {
                cartSize = cartSize - 1;
                printf("  Undid last ingredient.\n");
            } else {
                printf("  Nothing to undo.\n");
            }
            pauseAnyKey();
        }

        if (action == 4) {
            if (cartSize == 0) {
                printf("  Add some ingredients first~\n");
                pauseAnyKey();
            } else {
                running = 0;
            }
        }

        if (action == 5) {
            if (cartSize > 0) {
                printf("  Are you sure? Everything will be lost.\n");
                printf("    1. Yes, go back\n    2. No, stay\n  Choice: ");
                scanf("%d", &cc);
                if (cc == 1) {
                    return;
                }
            } else {
                return;
            }
        }
    }

    /* checkout */

    printf("\n  ===== YOUR CUSTOM DRINK =====\n\n");
    printf("  Cup: %s (%d ml)\n\n", cupSizes[cupChoice - 1].name, cupMl);

    for (i = 0; i < cartSize; i++) {
        char *n;
        int p;
        int ml;

        if (cart[i].isTopping == 1) {
            n = toppingIngredients[cart[i].index].name;
            p = toppingIngredients[cart[i].index].price * cart[i].portions;
            ml = toppingIngredients[cart[i].index].ml * cart[i].portions;
        } else {
            n = baseIngredients[cart[i].index].name;
            p = baseIngredients[cart[i].index].price * cart[i].portions;
            ml = baseIngredients[cart[i].index].ml * cart[i].portions;
        }

        printf("  %2d. %-30s x%d  %dml  %dTk\n", i + 1, n, cart[i].portions, ml, p);
    }

    printf("  -----------------------------------------\n");
    printf("  Total filled: %d ml / %d ml\n", totalMl(), cupMl);
    printf("  TOTAL PRICE:  %d Tk\n", totalPrice());
    printf("  -----------------------------------------\n");

    printf("\n  Select payment method:\n");
    printf("    1. Cash\n    2. bKash\n    3. Nagad\n\n  Choice: ");
    scanf("%d", &pay);

    if (pay < 1 || pay > 3) {
        pay = 1;
    }

    if (pay == 1) {
        strcpy(payName, "Cash");
    } else if (pay == 2) {
        strcpy(payName, "bKash");
    } else {
        strcpy(payName, "Nagad");
    }


    printf("\n  Yay! Can't wait for the drink! ^_^\n\n");
    printf("  Payment via %s confirmed.\n", payName);
    printf("  Total: %d Tk\n\n", totalPrice());
    pauseAnyKey();
}

int main(void) {
    int choice;

    initData();

    while (1) {

        printf("\n  ================================\n");
        printf("    ~*~ TAP TAP COFFEE ~*~\n");
        printf("    Your cute drink corner!\n");
        printf("  ================================\n\n");
        printf("  Welcome to Tap Tap Coffee!\n");
        printf("  Pick your adventure:\n\n");
        printf("    1. Normal Menu  - Choose from our lovely drinks\n");
        printf("    2. Custom Menu  - Create your own adorable drink!\n");
        printf("    3. Exit\n\n  Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            showNormalMenu();
        }

        if (choice == 2) {
            showCustomMenu();
        }

        if (choice == 3) {
    
            printf("\n  Bye-bye! Come back soon for more yummy drinks!\n\n");
            return 0;
        }

        if (choice != 1 && choice != 2 && choice != 3) {
            printf("  Invalid choice!\n");
            pauseAnyKey();
        }
    }

    return 0;
}
