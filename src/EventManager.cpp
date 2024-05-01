#include "EventManager.hpp"

fd_set          EventManager::_read;
fd_set          EventManager::_write;

void EventManager::start() {
    FD_ZERO(&_read);
    FD_ZERO(&_write);
}

void EventManager::addWriteFd(int fd)
{
    FD_SET(fd, &_write);
};

void EventManager::addReadFd(int fd)
{
    FD_SET(fd, &_read);
};

void EventManager::delWriteFd(int fd)
{
    FD_CLR(fd, &_write);
};

void EventManager::delReadFd(int fd)
{
    FD_CLR(fd, &_read);
};