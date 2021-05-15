const path = require('path');

module.exports = {
  mode: 'development',
  entry: [ 'babel-polyfill', './src/index.js' ],
  output: {
    path: path.resolve(__dirname, 'public'),
    filename: 'bundle.js'
  },
  devServer: {
    contentBase: path.join(__dirname, 'public'),
    compress: true,
  },
  module: {
    rules: [
      {
        test: /\.m?js$/,
        exclude: /(node_modules|bower_components)/,
        use: {
          loader: 'babel-loader',
          options: {
            presets: ['@babel/preset-env', '@babel/preset-react'],
            plugins: ["transform-class-properties"]
          }
        }
      },
      {
        test: /\.css$/,
        use: ['style-loader','css-loader']
      }
    ]
  }

};

