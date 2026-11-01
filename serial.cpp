#include "serial.h"
#include <libusbp.hpp>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdexcept>

const uint16_t kVendorId = 0x0403;
const uint16_t kProductId = 0x6001;

std::string find_serial_port() {
    libusbp::device device =
        libusbp::find_device_with_vid_pid(kVendorId, kProductId);
    libusbp::serial_port port(device);
    return port.get_name();
}

int open_serial(const std::string& port_name) {
    int fd = open(port_name.c_str(), O_RDWR | O_NOCTTY);
    if (fd < 0) {
        throw std::runtime_error("Gagal membuka " + port_name);
    }
    termios tty{};
    tcgetattr(fd, &tty);
    // Mode raw: byte dilewatkan tanpa diubah (8N1)
    cfmakeraw(&tty);
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);
    tcsetattr(fd, TCSANOW, &tty);
    return fd;
}

void send_serial(int fd, const std::string& data) {
    write(fd, data.data(), data.size());
}
