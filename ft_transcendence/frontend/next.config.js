/** @type {import('next').NextConfig} */
const nextConfig = {
  reactStrictMode: true,
  async rewrites() {
    return [
      {
        source: '/api/:path*',
        destination: 'https://backend:3001/:path*'
      }
    ];
  },
  // Enable HTTPS in development
  experimental: {
    https: true
  },
  // Add HTTP to HTTPS redirect
  async redirects() {
    return [
      {
        source: '/:path*',
        has: [
          {
            type: 'header',
            key: 'x-forwarded-proto',
            value: 'http'
          }
        ],
        permanent: true,
        destination: 'https://frontend:3000/:path*'
      }
    ];
  }
};

module.exports = nextConfig;