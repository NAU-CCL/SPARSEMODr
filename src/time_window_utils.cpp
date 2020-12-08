#include "time_window_utils.h"


/*
 * Adds a TimeWindow to the linked list where "node" points to the head of
 *   the linked list.
 * "new_node" must be allocated and populated with data before calling this
 *   function.
 */
TimeWindow *addTimeWindow(TimeWindow *node, TimeWindow *new_node)
{
    if (node == NULL)
    {
        return new_node;
    }
    else
    {
        node->next = addTimeWindow(node->next, new_node);
        node->next->prev = node;
    }
    return node;
}


/*
 * Frees the memory used in the linked list. When first called, "node" should
 *   point to the head of the linked list.
 */
void clearTimeWindows(TimeWindow *node)
{
    if (node->next != NULL)
    {
        clearTimeWindows(node->next);
    }
    node->prev = NULL;
    delete node;
}


/*
 * Creates the time windows from the imported data.
 */
TimeWindow *importTimeWindowData(int total,
                                 double *r0,
                                 double *dist_param,
                                 double *m,
                                 double *imm_frac,
                                 double *hosp_rate,
                                 double *icu_rate,
                                 double *death_rate,
                                 double *recov_hosp,
                                 int *window_length)
{
    TimeWindow *head_node = NULL;
    TimeWindow *temp_node = NULL;

    int index = 0;

    // If the first time window is longer than 1 day, we need to make a time window
    // for the initial values with length 0 days.
    if (window_length[0] > 1)
    {
        temp_node = new TimeWindow();
        temp_node->r0 = r0[0];
        temp_node->dist_param = dist_param[0];
        temp_node->m = m[0];
        temp_node->imm_frac = imm_frac[0];
        if (hosp_rate != NULL) temp_node->hosp_rate = hosp_rate[0];
        if (icu_rate != NULL) temp_node->icu_rate = icu_rate[0];
        if (death_rate != NULL) temp_node->death_rate = death_rate[0];
        if (recov_hosp != NULL) temp_node->recov_hosp = recov_hosp[0];
        temp_node->window_length = 0;
        temp_node->prev = NULL;
        temp_node->next = NULL;
        head_node = addTimeWindow(head_node, temp_node);
    }

    // Create the linked list of time windows as normal
    while (index < total)
    {
        temp_node = new TimeWindow();
        temp_node->r0 = r0[index];
        temp_node->dist_param = dist_param[index];
        temp_node->m = m[index];
        temp_node->imm_frac = imm_frac[index];
        if (hosp_rate != NULL) temp_node->hosp_rate = hosp_rate[index];
        if (icu_rate != NULL) temp_node->icu_rate = icu_rate[index];
        if (death_rate != NULL) temp_node->death_rate = death_rate[index];
        if (recov_hosp != NULL) temp_node->recov_hosp = recov_hosp[index];
        temp_node->window_length = window_length[index];
        temp_node->prev = NULL;
        temp_node->next = NULL;
        head_node = addTimeWindow(head_node, temp_node);

        index++;
    }

    return head_node;
}
