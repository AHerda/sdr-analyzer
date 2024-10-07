#pragma once

#include "units.hpp"

#include <libairspy/airspy.h>

#include <cstdint>

class AirSpy
{
public:
    AirSpy();
    ~AirSpy();

    /// @brief Open the device
    void open();
    /// @brief Close the device
    void close();

    /// @brief Set the frequency
    void setFrequency(uint32_t frequency_);
    /// @brief Set the sample rate
    void setSampleRate(uint32_t sampleRate_);
    /// @brief Set the sample type
    void setSampleType(airspy_sample_type sampleType_);
    /// @brief Set the LNA gain
    void setLnaGain(uint8_t lnaGain_);
    /// @brief Set the Mixer gain
    void setMixerGain(uint8_t mixerGain_);
    /// @brief Set the VGA gain
    void setVgaGain(uint8_t vgaGain_);
    /// @brief Set the Linearity gain
    void setLinearityGain(uint8_t linearityGain_);
    /// @brief Set the Sensitivity gain
    void setSensitivityGain(uint8_t sensitivityGain_);
    /// @brief Set the LNA AGC
    void setLnaAgc(bool lnaAgc_);
    /// @brief Set the Mixer AGC
    void setMixerAgc(bool mixerAgc_);
    /// @brief Set the RF bias
    void setRfBias(bool rfBias_);
    /// @brief Set the packing
    void setPacking(bool packing_);

    /// @brief Read the part ID and serial number
    void readPartIdSerialNo();

    /// @brief Starts the reception process
    /// @param callback The callback function
    /// @param userData The user data
    void startRx(airspy_sample_block_cb_fn callback, void* userData);
    void stopRx();

    void setSi5351cRegister(uint8_t registerNumber, uint8_t value);
    void readSi5351cRegister(uint8_t registerNumber, uint8_t* value);
    void setR820tRegister(uint8_t registerNumber, uint8_t value);
    void readR820tRegister(uint8_t registerNumber, uint8_t* value);
    void writeConfig(uint8_t pageIndex, uint16_t length, unsigned char* data);
    void readConfig(uint8_t pageIndex, uint16_t length, unsigned char* data);
    void writeGpio(airspy_gpio_port_t port, airspy_gpio_pin_t pin, uint8_t value);
    void readGpio(airspy_gpio_port_t port, airspy_gpio_pin_t pin, uint8_t* value);
    void writeGpioDir(airspy_gpio_port_t port, airspy_gpio_pin_t pin, uint8_t value);
    void readGpioDir(airspy_gpio_port_t port, airspy_gpio_pin_t pin, uint8_t* value);
    void eraseSpiflash();
    void writeSpiflash(uint32_t address, uint16_t length, unsigned char* data);
    void readSpiflash(uint32_t address, uint16_t length, unsigned char* data);
    void readBoardId(uint8_t* value);
    void readVersionString(char* version, uint8_t length);

private:
    airspy_device* device;
    airspy_read_partid_serialno_t serial;

    /// @brief Frequency in Hz
    /// @note The frequency must be between 24MHz and 1.75GHz.
    /// @note The default value is 100MHz.
    uint32_t frequency{433_MHz};//{102'300_kHz};
    /// @brief Sample rate in Hz
    /// @note The sample rate must be either 3MHz or 6MHz.
    /// @note The default value is 6MHz.
    uint32_t sampleRate{3_MHz};
    /**
     * @brief Sample type
     * @note The sample type can be one of the following: @n
     * - AIRSPY_SAMPLE_FLOAT32_IQ @n
     * - AIRSPY_SAMPLE_FLOAT32_REAL @n
     * - AIRSPY_SAMPLE_INT16_IQ @n
     * - AIRSPY_SAMPLE_INT16_REAL @n
     * - AIRSPY_SAMPLE_UINT16_REAL @n
     * - AIRSPY_SAMPLE_RAW @n
     * - AIRSPY_SAMPLE_END @n
     * @note The default value is AIRSPY_SAMPLE_RAW.
     */
    airspy_sample_type sampleType{airspy_sample_type::AIRSPY_SAMPLE_RAW};

    /// @brief LNA gain
    /// @note The LNA gain must be between 0 and 15.
    /// @note The default value is 7.
    uint8_t lnaGain{7};
    /// @brief Mixer gain
    /// @note The Mixer gain must be between 0 and 15.
    /// @note The default value is 7.
    uint8_t mixerGain{7};
    /// @brief VGA gain
    /// @note The VGA gain must be between 0 and 15.
    /// @note The default value is 7.
    uint8_t vgaGain{7};
    /// @brief Linearity gain
    /// @note The Linearity gain must be between 0 and 21.
    /// @note The default value is 10.
    uint8_t linearityGain{10};
    /// @brief Sensitivity gain
    /// @note The Sensitivity gain must be between 0 and 21.
    /// @note The default value is 10.
    uint8_t sensitivityGain{10};
    bool lnaAgc{false};
    bool mixerAgc{false};
    bool rfBias{false};
    bool packing{false};
};
