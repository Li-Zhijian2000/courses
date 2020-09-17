const path = require('path')

const name = 'rent system';

const resolve = dir => path.join(__dirname, dir);

module.exports = {
  // devServer: {
  //   proxy: {
  //     '/api': {
  //       target: 'http://localhost:8181',
  //       changeOrigin: true,
  //       ws: true,
  //       pathRewrite: {
  //         '^/api': '/'
  //       }
  //     }
  //   }
  // },

  configureWebpack: {
    name: name,
    resolve: {
      alias: {
        '@': resolve('src'),
      }
    }
  }

}
