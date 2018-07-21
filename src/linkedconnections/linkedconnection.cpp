#include "linkedconnection.h"

LinkedConnection::LinkedConnection(QObject *parent) : QObject(parent)
{
    // Set parent of this QObject. When parent is destroyed, this one is automatically cleaned up too.
    this->setParent(parent);


}
