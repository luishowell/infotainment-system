#ifndef MUTEX_H
#define MUTEX_H
/**
 * @brief Mutexes for access to hardware. Used to keep classes thread safe.
 * 
 */
namespace Mutex
{
    /**
     * @brief Obtains mutex lock for OBD2 bus and blocks if busy
     * 
     */
    void LockOBD2();

    /**
     * @brief Attempts to lock the OBD2 bus but is non-blocking
     * 
     * @return true OBD2 bus successfully locked
     * @return false OBD2 bus not locked
     */
    bool TryOBD2();

    /**
     * @brief Gives back the lock to the OBD2 bus
     * 
     */
    void UnlockOBD2();
}

#endif //MUTEX_H