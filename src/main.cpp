#include <std_include.hpp>

#include "utils/cryptography.hpp"

#include "console.hpp"
#include "crypto_key.hpp"

#include "network/address.hpp"
#include "network/socket.hpp"

using namespace std::literals;

namespace
{
	utils::cryptography::ecc::key key;

	const char* master_address = "master.xlabs.dev";
	std::uint16_t master_port = 20810;
	const char* to_kill = nullptr;
	const char* to_remove = nullptr;
	const char* reason = "Admin abuse, please demote";

	std::string format_command(const bool add)
	{
		std::string cmd = "\xFF\xFF\xFF\xFFpatchkill";
		const auto line = [&cmd](const std::string& text)
		{
			cmd.append(" ");
			cmd.append(text);
		};

		const auto current_timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
		const auto to_sign = std::to_string(current_timestamp.count());

		line(to_sign);

		const auto signed_timestamp = utils::cryptography::ecc::sign_message(key, to_sign);

		line(utils::cryptography::base64::encode(signed_timestamp));

		line((add ? "add"s : "remove"s));

		line((add ? std::string(to_kill) : std::string(to_remove)));

		line(std::string(reason));

		return cmd;
	}

	void unsafe_main()
	{
		key = crypto_key::get();

		network::address master(master_address);
		master.set_port(master_port);

		const network::socket s;

		if (to_kill != nullptr)
		{
			const auto packet = format_command(true);
			s.send(master, packet);

			console::info("Sent kill command to %s", master.to_string().data());
		}
		else if (to_remove != nullptr)
		{
			const auto packet = format_command(false);
			s.send(master, packet);

			console::info("Sent remove command to %s", master.to_string().data());
		}
	}

	void usage(const char* prog)
	{
		console::error("X Labs Master Tool\n"
			"Usage: %s OPTIONS\n"
			"  -master IP - set the target, default: '%s'\n"
			"  -port PORT - set the port, default: '%hu'\n"
			"  -add IP - remove ip address from the server list\n"
			"  -remove IP - allow ip address back on the server list\n"
			"  -reason - set a reason, default: '%s'",
			prog, master_address, master_port, reason
		);
	}
}

int main(const int argc, const char** argv)
{
	console::set_title("X Labs Master Tool");
	console::log("Starting X Labs Master Tool");

	// Parse command-line arguments
	for (auto i = 1; i < argc; i++)
	{
		if (std::strcmp(argv[i], "-master") == 0)
		{
			master_address = argv[++i];
		}
		else if (std::strcmp(argv[i], "-port") == 0)
		{
			master_port = static_cast<std::uint16_t>(std::strtol(argv[++i], nullptr, 0));
		}
		else if (std::strcmp(argv[i], "-add") == 0)
		{
			to_kill = argv[++i];
		}
		else if (std::strcmp(argv[i], "-remove") == 0)
		{
			to_remove = argv[++i];
		}
		else if (std::strcmp(argv[i], "-reason") == 0)
		{
			reason = argv[++i];
		}
		else
		{
			usage(argv[0]);
			return EXIT_FAILURE;
		}
	}

	try
	{
		unsafe_main();
	}
	catch (const std::exception& ex)
	{
		console::error("Fatal error: %s", ex.what());
		return EXIT_FAILURE;
	}

	console::log("Terminating tool...");
	return EXIT_SUCCESS;
}
