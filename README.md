# OKXTradingSystem: 
 **Created an order execution and management system to trade on OKX**

      *Functions*

            - Place order

            - Cancel order

            - Modify order

            - Get orderbook

            - View current positions

      Scope:

            - Spot and futures

            - All supported symbols

      Focus:

            - Full functionality of above functions with low latency
            - create 1 contract of MATIC-USDT-SWAP.

## To run the OKXTradingSystem project locally, you'll need to follow these steps:

1. **Clone the Repository**: 
   ```
   git clone https://github.com/manni2000/OKXTradingSystem.git
   ```
2. **Navigate to the Project Directory**:
   ```
   cd OKXTradingSystem
   ```

3. **Set Up the Build Environment**:
   - Ensure you have CMake installed and correctly set up.
   - Install MinGW64, and make sure its `bin` directory is included in your system's PATH.

4. **Build the Project**:
   - Create a `build` directory:
     ```
     mkdir build
     cd build
     ```
   - Generate the build files using CMake:
     ```
     cmake .. -G "MinGW Makefiles"
     ```
   - Compile the project:
     ```
     mingw32-make
     ```

5. **Resolve Dependencies**:
   - The errors you encountered are related to missing references to `Json::Value` and `curl` functions, indicating that the JSON and CURL libraries were not correctly linked. 
   - Ensure that you have built the `libjsoncpp.a` library correctly using MinGW64, and that it's linked properly in the CMake configuration. Also, verify that the CURL library is correctly linked and compiled for MinGW.

6. **Run the Application**:
   - Once the build completes without errors, you should be able to run the executable (`OKXTradingSystem.exe`) generated in the `build` directory.
