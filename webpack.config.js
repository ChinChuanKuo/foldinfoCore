const path = require('path');
const sourcePath = path.resolve(__dirname, 'wwwroot');
const publicPath = `${sourcePath}/dist/`;

module.exports = {
    entry: `${sourcePath}/js/Index.bs.js`,
    output: {
        filename: 'bundle.js',
        path: `${publicPath}/js/`
    },
    context: __dirname,
    devServer: {
        compress: true,
        contentBase: publicPath,
        historyApiFallback: true
    },
    module: {
        rules: [
            {
                test: /\.(png|jpg|gif|svg)$/,
                use: [{ loader: "url-loader" }]
            },
            {
                test: /\.scss$/,
                use: [{ loader: "style-loader" }, { loader: "css-loader" }, { loader: "sass-loader" }]
            },
            {
                test: /\.css$/,
                use: [{ loader: "style-loader" }, { loader: "css-loader" }]
            }
        ]
    }
}