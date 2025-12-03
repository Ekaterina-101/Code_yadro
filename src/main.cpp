#include "../include/noise.hpp"
#include "../include/crc.hpp"
#include "../include/modem.hpp"

int main() {
    std::vector<int> w = {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1};

    CRC8 crc;
    std::vector<int> CRCencoded = crc.encodeCRC(w);


    std::vector<double> BPSKsigal = BPSKmod(CRCencoded);
    std::vector<double> noisedSignal1 = BSC(0.0, BPSKsigal);
    std::vector<int> BPSKdeSignal = BPSKdemod(noisedSignal1);

    std::vector<double> BPSKsigalAWGN_B = BPSKmod(CRCencoded);
    std::vector<double> noisedSignal2 = AWGN_B(0.0, BPSKsigalAWGN_B);
    std::vector<int> BPSKdeSignalAWGN_B = BPSKdemod(noisedSignal2);

    std::vector<complex> BPSKsigalAWGN_Q = QPSKmod(CRCencoded);
    std::vector<complex> noisedSignal3 = AWGN_Q(0.0, BPSKsigalAWGN_Q);
    std::vector<int> BPSKdeSignalAWGN_Q = QPSKdemod(noisedSignal3);


    bool CRCdecoded = crc.decodeCRC(BPSKdeSignal);
}
