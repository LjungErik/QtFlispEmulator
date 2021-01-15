#include "io.h"

IO::IO()
{
    /* Initialize ports to null */
    m_outputs[FB_PORT] = IOPort();
    m_outputs[FC_PORT] = IOPort();
    m_inputs[FB_PORT] = IOPort();
    m_inputs[FC_PORT] = IOPort();
}

bool IO::registerOutput(uint8_t port) 
{
    if (m_outputs.find(port) == m_outputs.end()) {
        return false;
    }
    m_outputs[port].activate();
    return true;
}

bool IO::unregisterOutput(uint8_t port)
{
    if (m_outputs.find(port) == m_outputs.end()) {
        return false;
    }

    m_outputs[port].deactivate();
    return true;
}

bool IO::registerInput(uint8_t port, uint8_t value) 
{
    if (m_inputs.find(port) == m_inputs.end()) {
        return false;
    }
    m_inputs[port].setValue(value);
    m_inputs[port].activate();
    return true;
}

bool IO::unregisterInput(uint8_t port)
{
    if (m_inputs.find(port) == m_inputs.end()) {
        return false;
    }

    m_inputs[port].setValue(0x00);
    m_inputs[port].deactivate();
    return true;
}

bool IO::isIOPort(uint8_t port) {
    return port == FB_PORT || port == FC_PORT;
}

uint8_t IO::readPort(uint8_t port)
{
    if (isIOPort(port))
    {
        if (m_inputs[port].isActive()) {
            return m_inputs[port].getValue();
        }

        return m_outputs[port].getValue();
    }

    return 0;
}

bool IO::writeOutput(uint8_t port, uint8_t value)
{
    if (isIOPort(port))
    {
        if (m_inputs[port].isActive()) {
            //If it is a input port then change nothing
            //TODO figure out if this really is the correct way
            //to handle this
            return false;
        }

        m_outputs[port].setValue(value);
        return true;
    }
    return false;
}

bool IO::updateInput(uint8_t port, uint8_t value)
{
    if (isIOPort(port) && m_inputs[port].isActive())
    {
        m_inputs[port].setValue(value);
        return true;
    }
    return false;
}