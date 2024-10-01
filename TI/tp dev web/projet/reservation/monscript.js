function Poster() {
  let id = document.getElementById("characterId").value;
  let nom = document.getElementById("nom").value;
  let prenom = document.getElementById("prenom").value;
  let NUM = document.getElementById("NUM").value;
  let email = document.getElementById("email").value;
  let typeVoiture = document.getElementById("typeVoiture").value;

  if (id) {
      
      updateCharacter(parseInt(id), nom, prenom, NUM, email, typeVoiture);
  } else {
      
      let newCharacter = {
          id: Math.floor(Math.random() * 1000),
          nom: nom,
          prenom: prenom,
          NUM: NUM,
          email: email,
          typeVoiture: typeVoiture,
          
      };
      storeNewCharacter(newCharacter);
  }

 
  document.getElementById("characterForm").reset();
  document.getElementById("characterId").value = '';
}

function updateCharacter(id, nom, prenom, NUM, email, typeVoiture) {
  let characters = JSON.parse(localStorage.getItem('characters')) || [];
  let characterIndex = characters.findIndex(character => character.id === id);
  if (characterIndex > -1) {
      characters[characterIndex].nom = nom;
      characters[characterIndex].prenom = prenom;
      characters[characterIndex].NUM = NUM;
      characters[characterIndex].email = email;
      characters[characterIndex].typeVoiture = typeVoiture;
      localStorage.setItem('characters', JSON.stringify(characters));
      refreshCharactersList();
  }
}

function insertNewCharacterToDom(ch) {
  let article = document.createElement('article');
  article.classList.add('card', 'mb-2');
  article.innerHTML = `
      <div class="card-body d-md-flex justify-content-between align-items-center">
          <div class="info d-md-flex align-items-center">
              <h4 class="card-title mb-0 mr-3">${ch.nom} ${ch.prenom}</h4>
              <h5 class="mb-0 mr-3">${ch.NUM}</h5>
              <h5 class="mb-0 mr-3">${ch.typeVoiture}</h5>
          </div>
          <div class="buttons-row">
              <button class="btn  btn-secondary edit-button mr-2" data-id="${ch.id}">Modifier</button>
              <button class="btn btn-danger delete-button" data-id="${ch.id}">Supprimer</button>
          </div>
      </div>
  `;
  document.getElementById('contenu').appendChild(article);

  let deleteButton = article.querySelector('.delete-button');
  deleteButton.addEventListener('click', function() {
      let characterId = this.getAttribute('data-id');
      deleteCharacter(characterId);
  });

  let editButton = article.querySelector('.edit-button');
  editButton.addEventListener('click', function() {
      let characterId = this.getAttribute('data-id');
      editCharacter(characterId);
  });
}

function editCharacter(id) {
  let characters = JSON.parse(localStorage.getItem('characters')) || [];
  let character = characters.find(character => character.id === parseInt(id));
  if (character) {
      document.getElementById("characterId").value = character.id;
      document.getElementById("nom").value = character.nom;
      document.getElementById("prenom").value = character.prenom;
      document.getElementById("NUM").value = character.NUM;
      document.getElementById("email").value = character.email;
      document.getElementById("typeVoiture").value = character.typeVoiture;
  }
}

function refreshCharactersList() {
  document.getElementById('contenu').innerHTML = ''; 
  let characters = JSON.parse(localStorage.getItem('characters')) || [];
  if (characters) {
      characters.forEach(character => {
          insertNewCharacterToDom(character);
      });
  }
}

function storeNewCharacter(newCharacter) {
  let characters = JSON.parse(localStorage.getItem('characters')) || [];
  characters.push(newCharacter);
  localStorage.setItem('characters', JSON.stringify(characters));
  refreshCharactersList();
}

function deleteCharacter(id) {
  let characters = JSON.parse(localStorage.getItem('characters'));
  let updatedCharacters = characters.filter(character => character.id !== parseInt(id));
  localStorage.setItem('characters', JSON.stringify(updatedCharacters));
  refreshCharactersList();
}
function effacerTousContacts() {

  localStorage.removeItem('characters');
  refreshCharactersList();
}
 //pour mettre le non de la voiture dans le champ input de formulaire 
const params = new URLSearchParams(window.location.search);
        const typeVoiture = params.get('type');
        document.getElementById('typeVoiture').value = typeVoiture;
//fin

//fonction de recherche d'un contact 
function rechercherContact() {
  let searchNUM = document.getElementById("searchNUM").value;
  let characters = JSON.parse(localStorage.getItem('characters')) || [];
  let found = false;

  for (let i = 0; i < characters.length; i++) {
    if (characters[i].NUM === searchNUM) {
      found = true;
      break;
    }
  }

  let resultatRecherche = document.getElementById("resultatRecherche");
  if (found) {
    resultatRecherche.textContent = `Le contact avec le numéro ${searchNUM} existe.`;
  } else {
    resultatRecherche.textContent = `Le contact avec le numéro ${searchNUM} n'existe pas.`;
  }
}
//fin du fonction 



// Initial call to populate the list
refreshCharactersList();
