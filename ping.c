#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define _MAIL "" // to which address to sent the mail
#define _DELAY 10 // delay between pings in seconds
#define _MAIL_DELAY 1 // delay between emails in hours

/**
 * @brief Checks for the validity of the given IP address
 * 
 * @param ip IPv4 address represented by an array of chars
 * @return int 0 if ip is valid, 1 otherwise
 */
int check_validity(char* ip)
{
    int fst, snd, trd, fth;
    int result = sscanf(ip, "%d.%d.%d.%d", &fst, &snd, &trd, &fth);

    if (result != 4) {
        return 1;
    }

    if (fst > 255 || fst < 0) {
        return 1;
    }

    if (snd > 255 || snd < 0) {
        return 1;
    }

    if (trd > 255 || trd < 0) {
        return 1;
    }

    if (fth > 255 || fth < 0) {
        return 1;
    }

    return 0;
}

/**
 * @brief Gets the IPs from the given arguments, checks them and saves them
 *        to the given array.
 * 
 * @param arr array where to save the IPs
 * @param count amount of arguments
 * @param argv arguments themselves
 * @return int 0 if everything went as it should have, 1 otherwise
 */
int get_ip_adressess(char arr[5][16], int count, char** argv)
{
    for (int i = 1; i < count; i++) {
        if (check_validity(argv[i]) == 1) {
            printf("%d. address is not valid, please try again.\n", i);
            return 1;
        }
        strcpy(arr[i - 1], argv[i]);
    }

    return 0;
}

/**
 * @brief Pings the given IP by using the ping terminal command
 * 
 * @param addr address to ping
 * @return int 0 if all went well, 1 if any error occured
 */
int ping (char addr[16])
{   
    char cmd[46] = {0};
    sprintf(cmd, "ping -c1 -w1 %s > /dev/null 2>&1", addr);
    int x = system(cmd);
    fflush(stdout);
    return (x == 0) ? 0 : 1;
}

/**
 * @brief Sends mail about the given IP with the given timestamp.
 *        Recevieng email can be changed by changing the _MAIL macro.
 * 
 * @param addr address that failed to respond 
 * @param timestamp timestamp of when it happened
 * @return int 0 if email was successfully sent, 1 otherwise
 */
int send_mail(char addr[16], time_t timestamp)
{
    char filename[100];
    char cmd[200] = {0};
    tmpnam(filename);

    FILE* temp = fopen(filename, "w");
    if (temp == NULL) {
        perror("Failed to sent email.\n");
        return 1;
    }

    fprintf(temp, "A network ping to a computer failed.\n");
    fprintf(temp, "IP: %s\n", addr);
    fprintf(temp, "Timestamp: %s\n", ctime(&timestamp));
    fflush(temp);

    sprintf(cmd, "mutt -s 'Monitoring' %s < %s\n\n", _MAIL, filename);
    system(cmd);

    fclose(temp);
    unlink(filename);

    return 0;
}

/**
 * @brief Runtime logic
 * 
 * @param argc amount of cmd arguments
 * @param argv cmd arguments
 * @return int 0 if programm ended successfully
 */
int main(int argc, char** argv)
{
    if (argc == 1) {
        printf("No IPs provided, exiting.\n");
        return 1;
    }

    char ip_addresses[5][16] = {0}; // maximum size of an IPv4 IP adress is 15 characters + ending \0
    time_t times[5] = {0};
    if (get_ip_adressess(ip_addresses, argc, argv) == 1) {
        return 1;
    }

    int amount = argc - 1;
    int delay = _MAIL_DELAY * 3600;
    
    while(1) {
        for (int i = 0; i < amount; i++) {
            if (ping(ip_addresses[i]) == 1) {
                time_t timestamp = time(NULL);

                if (timestamp - times[i] >= delay) { // only send mail about this IP when it 
                                                     // wasn't already sent in the last hour
                    if (send_mail(ip_addresses[i], timestamp) == 1) {
                        continue;   // if the email wasn't send, do not update the time and try again next loop
                    }
                    times[i] = timestamp; // save the timestamp of last email sent
                }
        }
        sleep(_DELAY);
        }
    }
    return 0;
}