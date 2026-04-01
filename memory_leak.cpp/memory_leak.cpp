#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>


double getMemoryPSI() {
   std::ifstream psiFile("/proc/pressure/memory");
   std::string line;
   if (psiFile.is_open()) {
       while (std::getline(psiFile, line)) {
           if (line.find("full") != std::string::npos) {
               size_t pos = line.find("avg10=");
               if (pos != std::string::npos) {
                   return std::stod(line.substr(pos + 6, 4));
               }
           }
       }
   }
   return 0.0;
}

int main() {
   std::vector<char*> leaker;
   double threshold = 1.0;

   std::cout << "--- Smart OOM Stopper Activated ---" << std::endl;
   std::cout << "Target Threshold: %" << threshold << " PSI Full Stall" << std::endl;

   while (true) {

       try {
           char* block = new char[50 * 1024 * 1024];

           for(int i=0; i < 50 * 1024 * 1024; i += 4096) block[i] = 'A';
           leaker.push_back(block);
       } catch (const std::bad_alloc& e) {
           std::cerr << "The system blocked us!" << std::endl;
           break;
       }


       double currentPSI = getMemoryPSI();
       std::cout << "Current PSI: " << currentPSI << " Total Leakage: "
                 << leaker.size() * 50 << " MB" << std::endl;

       if (currentPSI > threshold) {
           std::cout << "\n!!! CRITICAL THRESHOLD HAS BEEN EXCEEDED!!!" << std::endl;
           std::cout << "The system is being cleaned without freezing..." << std::endl;

           for (char* b : leaker) delete[] b;
           leaker.clear();

           std::cout << "Memory cleared. Safe exit." << std::endl;
           break;
       }
       sleep(1);
   }
   return 0;
}
