#pragma once

namespace network
{
	class address
	{
	public:
		address();
		address(const std::string& addr);
		address(sockaddr_in& addr);

		void set_ipv4(in_addr addr);
		void set_port(unsigned short port);
		GSL_NODISCARD unsigned short get_port() const;

		GSL_NODISCARD sockaddr& get_addr();
		GSL_NODISCARD const sockaddr& get_addr() const;
		GSL_NODISCARD sockaddr_in& get_in_addr();
		GSL_NODISCARD const sockaddr_in& get_in_addr() const;

		GSL_NODISCARD bool is_local() const;
		GSL_NODISCARD std::string to_string(bool with_port = true) const;

		bool operator==(const address& obj) const;

		bool operator!=(const address& obj) const
		{
			return !(*this == obj);
		}

	private:
		sockaddr_in address_{};

		void parse(std::string addr);
		void resolve(const std::string& hostname);
	};
}

namespace std
{
	template <>
	struct hash<network::address>
	{
		std::size_t operator()(const network::address& a) const noexcept;
	};
}
