
#ifndef FMU_PROXY_REMOTE_SLAVE_HPP
#define FMU_PROXY_REMOTE_SLAVE_HPP

#include <fmuproxy/fmi/slave.hpp>
#include <fmuproxy/thrift/FmuService.h>

#include <filesystem>

using namespace apache::thrift;
using namespace apache::thrift::transport;

namespace fmuproxy::client
{

class remote_slave : public fmi::slave
{

private:
    const fmi::model_description modelDescription_;
    std::shared_ptr<thrift::FmuServiceClient> client_;
    std::shared_ptr<TTransport> transport_;
    std::unique_ptr<std::thread> thread_;

    bool freed = false;

public:
    remote_slave(const std::filesystem::path& fmu, const std::string& instanceName, fmi::model_description modelDescription);

    [[nodiscard]] const fmi::model_description& get_model_description() const override;

    void setup_experiment(double start_time, double stop_time, double tolerance) override;
    void enter_initialization_mode() override;
    void exit_initialization_mode() override;

    void step(double current_time, double step_size) override;

    void terminate() override;
    void freeInstance() override;

    void get_integer(const std::vector<fmi::value_ref>& vr, std::vector<int>& values) override;
    void get_real(const std::vector<fmi::value_ref>& vr, std::vector<double>& values) override;
    void get_string(const std::vector<fmi::value_ref>& vr, std::vector<std::string>& values) override;
    void get_boolean(const std::vector<fmi::value_ref>& vr, std::vector<bool>& values) override;

    void set_integer(const std::vector<fmi::value_ref>& vr, const std::vector<int>& values) override;
    void set_real(const std::vector<fmi::value_ref>& vr, const std::vector<double>& values) override;
    void set_string(const std::vector<fmi::value_ref>& vr, const std::vector<std::string>& values) override;
    void set_boolean(const std::vector<fmi::value_ref>& vr, const std::vector<bool>& values) override;

    ~remote_slave() override;
};

} // namespace fmuproxy::client

#endif //FMU_PROXY_REMOTE_SLAVE_HPP