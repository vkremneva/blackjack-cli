/**
 * @file status.h

 * @brief File containing enum with status codes for the result of the operation.
 * 
 */


#ifndef STATUS_H
#define STATUS_H

/**
 * @brief Status codes used to indicate the result of operation.
 */
typedef enum
{
    INIT,           /**< Initial value for declarations. */
    SUCCESS,        /**< Operation completed successfully. */
    FAILURE,        /**< Operation failed. */
} status_t;

#endif /* STATUS_H */