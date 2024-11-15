#include <AirSpy.hpp>
#include <DataProcessor.hpp>
#include <utils.hpp>

#include <libairspy/airspy.h>

#include <iostream>

AirSpy::AirSpy() {
    open();
    readPartIdSerialNo();

    setFrequency(frequency);
    setSampleRate(sampleRate);
    setSampleType(sampleType);
    setLnaGain(lnaGain);
    setMixerGain(mixerGain);
    setVgaGain(vgaGain);
    setLinearityGain(linearityGain);
    setSensitivityGain(sensitivityGain);
    setLnaAgc(lnaAgc);
    setMixerAgc(mixerAgc);
    setRfBias(rfBias);
    setPacking(packing);
}

AirSpy::~AirSpy() {
    std::cerr << "Closing device" << std::endl;
    // close();

    if (device) {
        std::cout << "Device is not null";
        free(device);
        device = nullptr;
    }
}

void AirSpy::open() {
    int result = airspy_open(&device);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error opening device");
    }
}

void AirSpy::close() {
    int result = airspy_close(device);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error closing device");
    }
}

void AirSpy::setFrequency(uint32_t frequency_) {
    frequency = frequency_;

    int result = airspy_set_freq(device, frequency);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting frequency");
    }
}

void AirSpy::setSampleRate(uint32_t sampleRate_) {
    sampleRate = sampleRate_;

    uint32_t sampleRatesCount;
    int result  = airspy_get_samplerates(device, &sampleRatesCount, 0);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error getting sample rates count");
    }

    uint32_t sampleRates[sampleRatesCount];
    result = airspy_get_samplerates(device, sampleRates, sampleRatesCount);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error getting sample rates");
    }

    for (uint32_t i = 0; i < sampleRatesCount; i++) {
        if (sampleRates[i] == sampleRate) {
            result = airspy_set_samplerate(device, sampleRate);
            if (result != airspy_error::AIRSPY_SUCCESS) {
                error(result, "Error setting sample rate");
            }

            return;
        }
    }

    error(
        airspy_error::AIRSPY_ERROR_INVALID_PARAM,
        "Invalid sample rate: " + std::to_string(sampleRate_),
        false
    );
    std::cout << "Supported sample rates: ";

    for (uint32_t i = 0; i < sampleRatesCount; i++) {
        std::cout << sampleRates[i] << " ";
    }
    std::cout << "\nSetting default: " << sampleRates[0] << std::endl;

    sampleRate = sampleRates[0];

    result = airspy_set_samplerate(device, sampleRates[0]);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting default sample rate");
    }
}

void AirSpy::setSampleType(airspy_sample_type sampleType_) {
    sampleType = sampleType_;
    int result = airspy_set_sample_type(device, sampleType);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting sample type");
    }
}

void AirSpy::setLnaGain(uint8_t lnaGain_) {
    lnaGain = lnaGain_;

    int result = airspy_set_lna_gain(device, lnaGain);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting LNA gain");
    }
}

void AirSpy::setMixerGain(uint8_t mixerGain_) {
    mixerGain = mixerGain_;

    int result = airspy_set_mixer_gain(device, mixerGain);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting mixer gain");
    }
}

void AirSpy::setVgaGain(uint8_t vgaGain_) {
    vgaGain = vgaGain_;

    int result = airspy_set_vga_gain(device, vgaGain);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting VGA gain");
    }
}

void AirSpy::setLinearityGain(uint8_t linearityGain_) {
    linearityGain = linearityGain_;

    int result = airspy_set_linearity_gain(device, linearityGain);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting linearity gain");
    }
}

void AirSpy::setSensitivityGain(uint8_t sensitivityGain_) {
    sensitivityGain = sensitivityGain_;

    int result = airspy_set_sensitivity_gain(device, sensitivityGain);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting sensitivity gain");
    }
}

void AirSpy::setLnaAgc(bool lnaAgc_) {
    lnaAgc = lnaAgc_;

    int result = airspy_set_lna_agc(device, lnaAgc);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting LNA AGC");
    }
}

void AirSpy::setMixerAgc(bool mixerAgc_) {
    mixerAgc = mixerAgc_;

    int result = airspy_set_mixer_agc(device, mixerAgc);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting mixer AGC");
    }
}

void AirSpy::setRfBias(bool rfBias_) {
    rfBias = rfBias_;

    int result = airspy_set_rf_bias(device, rfBias);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting RF bias");
    }
}

void AirSpy::setPacking(bool packing_) {
    packing = packing_;

    int result = airspy_set_packing(device, packing);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error setting packing");
    }
}

void AirSpy::readPartIdSerialNo() {
    int result = airspy_board_partid_serialno_read(device, &serial);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error reading part ID and serial number");
    }
}

void AirSpy::startRx(airspy_sample_block_cb_fn callback, void* userData) {
    int result = airspy_start_rx(device, callback, userData);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error starting RX");
    }
}

void AirSpy::startRx(void* userData) {
    startRx(
        [](airspy_transfer_t* transfer) -> int {
            return AirSpy::airpspyCallback(transfer);
        },
        userData
    );
}

void AirSpy::stopRx() {
    int result = airspy_stop_rx(device);
    if (result != airspy_error::AIRSPY_SUCCESS) {
        error(result, "Error stopping RX");
    }
}

int AirSpy::airpspyCallback(airspy_transfer_t* transfer) {
    std::vector<IQSample> samples;
    samples.reserve(transfer->sample_count);

    if (transfer->sample_type != airspy_sample_type::AIRSPY_SAMPLE_FLOAT32_IQ) {
        error(airspy_error::AIRSPY_ERROR_INVALID_PARAM, "Invalid sample type", false);
        return 1;
    }

    if (transfer->dropped_samples) {
        std::string message =
            //"Samples no. " + std::to_string(AirSpy::counter) +
            "\nDropped samples: " + std::to_string(transfer->dropped_samples);
        transfer->dropped_samples = 0;
        error(airspy_error::AIRSPY_ERROR_OTHER, message, false);
    }

    for (int i = 0; i < transfer->sample_count; i++) {
        samples.push_back(IQSample(((float*) transfer->samples)[i * 2], ((float*) transfer->samples)[i * 2 + 1]));
    }

    DataProcessor* dataProcessor = (DataProcessor*) transfer->ctx;
    dataProcessor->process(samples);

    // AirSpy::counter++;
    return 0;
}
