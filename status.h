#ifndef STATUS_H
#define STATUS_H

/**
 * @brief Status codes used to indicate the result of operations.
 */
typedef enum
{
    SUCCESS,        /**< Operation completed successfully. */
    FAILURE,        /**< Operation failed. */
    INPUT_SUCCESS,  /**< Input was successfully read and stored in the buffer. */
    INPUT_FAILURE,   /**< An error occurred while reading the input. */
    EXIT
} status_t;

#endif // STATUS_H