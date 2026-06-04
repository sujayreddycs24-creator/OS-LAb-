#include <stdio.h>

void FIFO(int pages[], int n, int frames)
{
    int frame[20], i, j, k = 0, fault = 0, found;

    for (i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            frame[k] = pages[i];
            k = (k + 1) % frames;
            fault++;
        }
    }

    printf("Page Faults = %d\n", fault);
}

void LRU(int pages[], int n, int frames)
{
    int frame[20], recent[20];
    int i, j, fault = 0, found, pos, min;

    for (i = 0; i < frames; i++)
    {
        frame[i] = -1;
        recent[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                recent[j] = i;
                break;
            }
        }

        if (!found)
        {
            pos = 0;
            min = recent[0];

            for (j = 1; j < frames; j++)
            {
                if (recent[j] < min)
                {
                    min = recent[j];
                    pos = j;
                }
            }

            frame[pos] = pages[i];
            recent[pos] = i;
            fault++;
        }
    }

    printf("Page Faults = %d\n", fault);
}

void Optimal(int pages[], int n, int frames)
{
    int frame[20];
    int i, j, k, fault = 0, found;
    int pos, farthest, index;

    for (i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            int empty = -1;

            for (j = 0; j < frames; j++)
            {
                if (frame[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            if (empty != -1)
            {
                frame[empty] = pages[i];
            }
            else
            {
                farthest = -1;
                pos = -1;

                for (j = 0; j < frames; j++)
                {
                    index = n;

                    for (k = i + 1; k < n; k++)
                    {
                        if (frame[j] == pages[k])
                        {
                            index = k;
                            break;
                        }
                    }

                    if (index > farthest)
                    {
                        farthest = index;
                        pos = j;
                    }
                }

                frame[pos] = pages[i];
            }

            fault++;
        }
    }

    printf("Page Faults = %d\n", fault);
}

int main()
{
    int n, frames, i;
    int pages[100];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    FIFO(pages, n, frames);
    LRU(pages, n, frames);
    Optimal(pages, n, frames);

    return 0;
}