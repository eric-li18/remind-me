module.exports = async function App(context) {
    if (context.event.isText) {
        await context.sendText('Hey there! I\'m the remind-me bot! \n\n I can help you schedule dates and remind you about upcoming important dates!');
    }
};
