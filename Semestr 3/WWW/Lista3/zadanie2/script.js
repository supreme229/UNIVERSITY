const brandSelectOption = document.getElementById('marka');
const modelSelectOption = document.getElementById('model');
const buttonAdd = document.getElementById('dodaj-pozycje');
const inputText = document.getElementById('nowa');
const radioOption = document.getElementsByName('rodzaj')

var brands =[
    {name:"Ford", value:"ford"},
    {name:"Fiat", value:"fiat"}
]

var models = {
    ford:[
        {name:"Focus", value:"focus"},
        {name:"Fiesta", value:"fiesta"}
        ],
    fiat:[
        {name:"Punto", value:"punto"},
        {name:"Bravo", value:"bravo"}
         ]}

function appendOptionToSelect(whichSelect, value, innerHTML)
{
    let option = document.createElement('option');
    option.value = value;
    option.innerHTML = innerHTML;
    whichSelect.appendChild(option);
}

function update_models()
{
    modelSelectOption.innerHTML = null;
    for(let model of models[brandSelectOption.value])
    {
        appendOptionToSelect(modelSelectOption,model.value,model.name);
    }
}

function update_brands()
{
    brandSelectOption.innerHTML = null;
    for(let brand of brands)
    {
        appendOptionToSelect(brandSelectOption,brand.value,brand.name);
    }
}

function add_thing()
{
    if(!inputText.value)
    {
        alert("Nie wpisałeś nazwy marki/modelu.");
    }
    else
    {
        for(let option of radioOption)
        {
            if(option.checked && option.value == "marka")
            {
                add_brand(inputText.value);
            }
            else if(option.checked && option.value == "model")
            {
                add_model(inputText.value);
            }
        }
        inputText.value=null;
    }
}

function add_brand(brand){
    let value = brand;
    let name = brand;
    brands.push({name, value});
    models[brand] = [];
    update_brands();
}

function add_model(model){
    let brand = brandSelectOption.value;
    let value = model;
    let name = model.toLowerCase();
    models[brand].push({name,value});
    update_models();
}

update_brands();
update_models();

brandSelectOption.addEventListener("change", update_models);
buttonAdd.addEventListener("click",add_thing);