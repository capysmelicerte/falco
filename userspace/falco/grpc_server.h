/*
Copyright (C) 2019 The Falco Authors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include <thread>
#include <string>

#include "grpc_server_impl.h"

namespace falco
{
namespace grpc
{

class server : public server_impl
{
public:
	server()
	{
	}
	server(std::string server_addr, int threadiness, std::string private_key, std::string cert_chain, std::string root_certs):
		m_server_addr(server_addr),
		m_threadiness(threadiness),
		m_private_key(private_key),
		m_cert_chain(cert_chain),
		m_root_certs(root_certs)
	{
	}
	virtual ~server() = default;

	void init(std::string server_addr, int threadiness, std::string private_key, std::string cert_chain, std::string root_certs);
	void thread_process(int thread_index);
	void run();
	void stop();

	// fixme(leodido) > wny the output::service:: ..?
	output::service::AsyncService m_svc;
	std::unique_ptr<::grpc::ServerCompletionQueue> m_completion_queue;

	// version::service::AsyncService m_version_svc;
	// std::unique_ptr<::grpc::ServerCompletionQueue> m_version_completion_queue;

private:
	std::string m_server_addr;
	int m_threadiness;
	std::string m_private_key;
	std::string m_cert_chain;
	std::string m_root_certs;

	std::unique_ptr<::grpc::Server> m_server;
	std::vector<std::thread> m_threads;
};

} // namespace grpc
} // namespace falco