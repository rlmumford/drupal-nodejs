1. Just enable the module as usual
2. Edit your views and add nodejs_block display for the views in block display that you want to autorefresh by nodejs, or use nodejs_page for the views in page display.
3. Configure the wrapper id of each view in the settings form. You will find the right wrapper id in the view preview. For a block it's by default ".view view-[machine-name]", for a page it must be the same.
4. If you are using custom templates for your views, and are not using the views default markup, you can also add a new div with a name that you can add to the wrapper configuration form.
