#include "../include/noise.hpp"
#include "../include/crc.hpp"
#include "../include/modem.hpp"

int main() {

    std::vector<int> w = {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1,1, 0, 1, 0, 1, 1,1, 0, 1, 0, 1, 1,1, 0, 1, 0, 1, 1,1, 0, 1, 0, 1, 1};
    CRC8 crc;
    std::vector<int> CRCencoded = crc.encodeCRC(w);
    for (int p = 0; p < 100; p += 5) {


        std::vector<double> BPSKsigal = BPSKmod(CRCencoded);
        std::vector<double> noisedSignal1 = BSC(p/100.0, BPSKsigal);
        std::vector<int> BPSKdeSignal = BPSKdemod(noisedSignal1);

        bool CRCdecoded = crc.decodeCRC(BPSKdeSignal);

        // for (int i = 0; i < w.size(); i++) {
        //     std::cout << w[i] << " ";
        // }
        // std::cout << std::endl;

        // for (int i = 0; i < BPSKdeSignal.size() - 1; i++) {
        //     std::cout << BPSKdeSignal[i] << " ";
        // }
        // std::cout << std::endl;

        int count_err_bit = 0;
        for (int i = 0; i < w.size(); i++) {
            if (w[i] != BPSKdeSignal[i]) {
                count_err_bit++;
            }
        }
        std::cout << "p = " << p/100.0 << " BER = " << double(count_err_bit)/w.size() << std::endl;
    }

    std::cout << "AWGN_B" << std::endl;
    for (double SNR = 0.001; SNR <= 1.0; SNR += 0.005) {
        std::vector<double> BPSKsigalAWGN_B = BPSKmod(CRCencoded);
        std::vector<double> noisedSignal2 = AWGN_B(SNR, BPSKsigalAWGN_B);
        std::vector<int> BPSKdeSignalAWGN_B = BPSKdemod(noisedSignal2);

        // for (int i = 0; i < w.size(); i++) {
        //     std::cout << w[i] << " ";
        // }
        // std::cout << std::endl;

        // for (int i = 0; i < BPSKdeSignalAWGN_B.size() - 1; i++) {
        //     std::cout << BPSKdeSignalAWGN_B[i] << " ";
        // }
        // std::cout << std::endl;


        int count_err_bit = 0;
        for (int i = 0; i < w.size(); i++) {
            if (w[i] != BPSKdeSignalAWGN_B[i]) {
                count_err_bit++;
            }
        }
        std::cout << "SNR = " << SNR << " BER = " << double(count_err_bit)/w.size() << std::endl;
    }

    std::cout << "AWGN_Q" << std::endl;
    for (double SNR = 0.001; SNR <= 1.0; SNR += 0.005) {
        std::vector<std::complex<double>> BPSKsigalAWGN_Q = QPSKmod(CRCencoded);
        std::vector<std::complex<double>> noisedSignal3 = AWGN_Q(SNR, BPSKsigalAWGN_Q);
        std::vector<int> BPSKdeSignalAWGN_Q = QPSKdemod(noisedSignal3);
        bool CRCdecoded = crc.decodeCRC(BPSKdeSignalAWGN_Q);


        int count_err_bit = 0;
        for (int i = 0; i < w.size(); i++) {
            if (w[i] != BPSKdeSignalAWGN_Q[i]) {
                count_err_bit++;
            }
        }
        std::cout << "SNR = " << SNR << " BER = " << double(count_err_bit)/w.size() << std::endl;
    }

}
